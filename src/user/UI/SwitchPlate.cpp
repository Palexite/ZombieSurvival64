#include "SwitchPlate.h"
#include "controller.h"
namespace UI {
SwitchPlate::SwitchPlate( 
    quadrant bounds,
    uint16_t fontId, 
    const std::vector<std::string>& options,
    const std::function<void(int)>& onSelect,
    float padding) {
        
    this->bounds = bounds;
    this->fontId = fontId;
    this->options = options;
    this->onSelect = onSelect;
    this->padding = padding;
}

void SwitchPlate::update(float deltaTime) {
    joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);
    
    if(presButtons.c_left) {
        switchOption(0);
    } else if(presButtons.c_right) {
        switchOption(1);
    }

    if(presButtons.a) {
        this->onSelect(this->select);
    }
}

void SwitchPlate::draw(float deltaTime) {
    float textX = 0;
    if(this->changingOption) {
        this->animDelta += deltaTime;

        float animRatio = this->animDelta / this->animTime;
        textX = this->bounds.x - ((this->prevSelect * this->padding) + ((this->select - this->prevSelect) * this->padding * animRatio));

        if(animRatio >= 1) {
            this->changingOption = false;
        }
    } else {
        textX = this->bounds.x -  this->select * this->padding;
    }

    for(int i = 0; i < (int)this->options.size(); i++) {
        if(i == this->select) {

        rdpq_text_printf(NULL, this->fontId, textX + i * this->padding, bounds.y, "%s", this->options[i].c_str());
        }
        else {
        rdpq_text_printf(NULL, this->fontId, textX + i * this->padding, bounds.y, "^02%s^00", this->options[i].c_str());    
        rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
        }
    }
}

void SwitchPlate::switchOption(bool direction) {
    debugf("Switching option\n");
    int16_t amount = direction ? -1 : 1;
    
    this->select += amount;

    this->prevSelect = this->select - amount;
    
    this->changingOption = true;
    this->animTime = 0.1f;
    this->animDelta = 0;

}
}