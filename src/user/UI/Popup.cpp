#include "Popup.h"
#include <algorithm>
#include "../../p64/assetTable.h"
#include "assets/assetManager.h"
#include "libdragon.h"
#include <string_view>
#include "math.h"

#include "style.h"
#include "utility/fonts.h"
#include "utility/splitscreen.h"


  Popup::~Popup() = default;
void Popup::Close() {
    this->closeRequest = true;
}

    Popup::Popup(float x, float y, int w, int h,

        const std::string& titleText, 
        const std::string& descText, 
        color_t bgColor, 
        std::string fontName, 
        const std::vector<std::string>& choices, 
        std::function<void(int)> choiceCallback, 
        P64::Object *owner)

        : x(x), y(y), w(w), h(h), titleText(titleText), descText(descText), fontName(fontName), bgColor(bgColor), choices(choices), choiceCallback(choiceCallback), owner(owner) {

        uint8_t divs = splitscreen::curScreenDivisions;

        //Keep font size the same if the screen is split for 2 players;

            if(splitscreen::curScreenDivisions == 2) {
                divs = 1;
            }
            this->fontId = fonts::getFont(fontName, FONTSIZE_SMALL, 1);
            
        };

void Popup::draw(float deltaTime) {

        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);

    
    this->curTime = std::clamp(this->curTime + deltaTime, 0.0f, this->EaseInDur);


    float curScale = 0;
    float ratio = std::clamp(this->curTime / this->EaseInDur, 0.0f, 1.0f);

    if(ratio > 1) ratio = 1;
    curScale = ratio;


        rdpq_blitparms_s bgParm = {};
    bgParm.scale_x = this->w;
    bgParm.scale_y = this->h;

            rdpq_blitparms_s fgParm = {};
    fgParm.scale_x = this->w * curScale * 0.8;
    fgParm.scale_y = this->h * curScale * 0.8;
        if(this->bgSprite) {

        color_t fgColor = this->bgColor;
        fgColor.r = std::clamp(fgColor.r + 25, 0, 255);
        fgColor.g = std::clamp(fgColor.g + 25, 0, 255);
        fgColor.b = std::clamp(fgColor.b + 25, 0, 255);
        
    rdpq_set_prim_color(this->bgColor);
    rdpq_sprite_blit(this->bgSprite, x, y, &bgParm);
    rdpq_set_prim_color(fgColor);


    float newX = x + w / 2 - (curScale * w/2);
    float newY = y + h / 2 - (curScale * h/2);
    rdpq_sprite_blit(this->bgSprite, newX, newY, &fgParm);
    
        } else {
            this->bgSprite = (sprite_t*)P64::AssetManager::getByIndex("tex/white.sprite"_asset);
        }


        rdpq_textparms_t TEXT_TITLE {
            .width = 400,
            .align = ALIGN_CENTER,
            .disable_aa_fix = true
    };

              rdpq_textparms_t TEXT_DESC{
          .width = (int16_t)(this->w * 0.7),
        .align = ALIGN_CENTER,
        .line_spacing = 8,
        .wrap = WRAP_WORD,
        .disable_aa_fix = false
 };

               rdpq_textparms_t TEXT_BUTTON{
          .width = 128,
        .align = ALIGN_CENTER,
        .disable_aa_fix = false
 };


 if(ratio >= 1.0f) {

        rdpq_text_print(&TEXT_DESC, 
            this->fontId, 
            this->x + 
            this->w*0.03, 
            this->y + this->h*0.25, 
            this->descText.c_str());

        rdpq_text_print(&TEXT_TITLE, 
            this->fontId, 
            this->x + this->w * 0.1,
             this->y, 
             this->titleText.c_str());


            float choiceSpace = (this->w * 0.8) / this->choices.size();
            int choiceW = 1;
            float choiceH = 32;

            sprite_t *buttonSpr = (sprite_t*)P64::AssetManager::getByIndex("tex/grad1.sprite"_asset);

        for(size_t i = 0; i < this->choices.size(); ++i) {

            float choiceX = this->x + (choiceSpace * i) + (choiceSpace / 2);
            float choiceY = this->y + this->h - 128;

            debugf("Choice %d: X = %f, Y = %f\n", i, choiceX, choiceY);
            color_t choiceColor = RGBA32(255, 255, 255, 255);
            choiceColor.r = std::clamp(bgColor.r + 50, 0, 255);
            choiceColor.g = std::clamp(bgColor.g + 50, 0, 255);
            choiceColor.b = std::clamp(bgColor.b + 50, 0, 255);
            choiceColor.a = 255;
            
            if(i == this->curChoice) {

                choiceColor.r = std::clamp(bgColor.r + 100, 0, 255);
                choiceColor.g = std::clamp(bgColor.g + 100, 0, 255);
                choiceColor.b = std::clamp(bgColor.b + 100, 0, 255);

            }

            UI::Gradient::DrawMiddleGradient(choiceX, choiceY - 16, choiceW * 128, choiceW * 256, choiceH, choiceColor);
            rdpq_text_print(&TEXT_BUTTON, this->fontId, choiceX - choiceW * 64, choiceY, this->choices[i].c_str());
        }
    }
}

    void Popup::update(float deltaTime) {
            joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    if(presButtons.c_left) {
        this->curChoice = (this->curChoice - 1 + this->choices.size()) % this->choices.size();
    } else if(presButtons.c_right) {
        this->curChoice = (this->curChoice + 1) % this->choices.size();
    }

    if(presButtons.a) {
        if(this->choiceCallback) {
        this->choiceCallback(this->curChoice);
        }
    }
    }
