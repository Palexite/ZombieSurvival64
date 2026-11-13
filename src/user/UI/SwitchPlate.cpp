#include "SwitchPlate.h"
#include "controller.h"
SwitchPlate::SwitchPlate( 
    uint16_t fontId, 
    const std::vector<std::string>& options,
    const std::function<void(int)>& onSelect) {
        
    this->fontId = fontId;
    this->options = options;
    this->onSelect = onSelect;
}

void SwitchPlate::switchOption(bool direction) {

    int16_t amount = direction ? 1 : -1;
    joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);
    
    this->select += amount;
    this->select = (this->select + this->options.size()) % this->options.size();
    this->prevSelect = this->select - amount;
    this->changingOption = true;
    this->animTime = 0;


}

