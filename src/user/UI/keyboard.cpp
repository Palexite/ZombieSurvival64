#include "keyboard.h"
#include "utility/ascii.h"
#include "utility/fonts.h"
#include "utility/eeprom.h"
#include <algorithm>
#include "UI/style.h"

namespace UI {

    Keyboard::Keyboard(const char* title, std::string fontName, std::string defaultInput, uint32_t maxChars) {

        this->title = title;

        this->fontId = fonts::getFont(EEPROM_GAME::CurUserSettings.gameFont, 2, 1);

        char* curChar = ASCII::getAllValidUserChars();
        this->validChars = curChar;

        this->inputText = defaultInput;

        this->maxChars = maxChars;
    };


    void Keyboard::draw(float deltaTime) {


        const char* curChar = this->validChars;
        uint8_t charCount = 0;
        uint8_t charIdx = 0;

        float charMargin = 40 + (480 * ( 1 - animRatio));
        int xStep = charCount % 12;
        int yStep = charCount / 12;

    rdpq_textparms_t TEXT_CHAR{
        .width = 32,
        .align = ALIGN_CENTER,
        .disable_aa_fix = false
    };

    rdpq_textparms_t TEXT_INPUT{
        .width = 512,
        .align = ALIGN_CENTER,
        .disable_aa_fix = false
    };

    rdpq_textparms_t TEXT_TITLE{
        .width = 512,
        .align = ALIGN_CENTER,
        .disable_aa_fix = false
    };

    rdpq_blitparms_s selectStyle = {};
        selectStyle.theta = cursorRotation;
        selectStyle.scale_x = 0.5;
        selectStyle.scale_y = 0.5;
            

        rdpq_text_print(&TEXT_TITLE, 
            this->fontId, 
            this->quad.x - 32, 
            this->quad.y - 128, 
            this->title);

        sprite_t *cursorSpr = (sprite_t*)P64::AssetManager::getByIndex("tex/selectCursor.sprite"_asset);
        
            Gradient::DrawMiddleGradient(this->quad.x  + this->quad.w / 2 - (charMargin/2), 
            this->quad.y - 16, 32, 
            this->quad.w, 8, 
            RGBA32(50, 50, 50, 255));

            rdpq_text_print(&TEXT_INPUT, 
                this->fontId, 
                this->quad.x - 32, 
                this->quad.y - 32, 
                inputText.c_str());

        while(*curChar != '\0') {

            char singleChar[] {*curChar, '\0'};
            bool isSelected = (select == charIdx);
            float finalX = (float)xStep * charMargin + this->quad.x;
            float finalY = (float)yStep * charMargin + this->quad.y;

            Gradient::DrawMiddleGradient(finalX, 
                finalY, 
                16, 
                32, 
                32, 
                isSelected ? RGBA32(125, 125, 255, 255) : RGBA32(25, 25, 25, 255));

            rdpq_text_print(&TEXT_CHAR, 
                this->fontId, 
                finalX - 16, 
                finalY + 24, 
                singleChar);

            charCount++;
            curChar++;
            charIdx++;
            xStep = charCount % rowSize;
            yStep = charCount / rowSize;

            if(isSelected) {
                rdpq_sprite_blit(cursorSpr, finalX, finalY, &selectStyle);
            }
        };
    };



    void Keyboard::update(float deltaTime) {

        cursorRotation += deltaTime;
        animDelta = std::clamp(animDelta + deltaTime, 0.0f, this->animTime);
        animRatio = animDelta / this->animTime;

        joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);
        

        if(presButtons.a) {

            if(this->inputText.length() != this->maxChars) {
                this->inputText = inputText + validChars[this->select];
            }

        } else if(presButtons.b) {

            if(!this->inputText.empty()) {
                this->inputText.pop_back();
            }

        }

        if(presButtons.start) {
            this->onEnterCallback(this->inputText);
        }

        if(presButtons.c_left) {
            select = std::clamp(select - 1, 0, 63);
        } else if(presButtons.c_right) {
            select = std::clamp(select + 1, 0, 63);
        } else if(presButtons.c_down) {
            select = std::clamp(select + rowSize, 0, 62);
        } else if(presButtons.c_up) {
            select = std::clamp(select - rowSize, 0, 62);
        }
    }

}