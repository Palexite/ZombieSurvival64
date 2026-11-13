#include "gradbutton.h"
#include <string_view>
#include <algorithm>

#include "utility/fonts.h"
#include "utility/eeprom.h"
#include "utility/splitscreen.h"


namespace UI {

    GradientButton::GradientButton(std::string text, quadrant quad, buttonScheme scheme, std::function<void()> onEnter)
            : text(text), quad(quad), scheme(scheme), onEnter(onEnter), isHovered(false) {

            this->fontId = fonts::getFont(EEPROM_GAME::CurUserSettings.gameFont, FONTSIZE_SMALL, splitscreen::curScreenDivisions);

            }

    GradientButton::~GradientButton() = default;

    void GradientButton::Enter() {
        if(this->onEnter) {
            this->onEnter();
        }
    }

    void GradientButton::draw(float deltaTime) {
        int w = this->quad.w;
        int h = this->quad.h;
        float x = this->quad.x;
        float y = this->quad.y;
    UI::Gradient::DrawMiddleGradient(x, y, w/2, w, h, isHovered ? scheme.hoverColor : scheme.baseColor);


const int16_t textWidth = std::clamp(
    static_cast<int16_t>(w), (int16_t)0, (int16_t)640);

    rdpq_textparms_t TEXT_BUTTON{
        .width = textWidth,
        .align = ALIGN_CENTER,
        .disable_aa_fix = false
    };

    rdpq_text_printf(&TEXT_BUTTON, this->fontId, x - w/2, y + h/2 + 4, this->text.c_str());

    }
}