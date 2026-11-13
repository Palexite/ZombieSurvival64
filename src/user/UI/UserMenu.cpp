#include "UserMenu.h"
#include "style.h"

#include <vector>
#include <string>
#include <cassert>


#include "utility/controllerpak.h"
#include "utility/fonts.h"
#include "utility/eeprom.h"

namespace UI {


    UserMenu::UserMenu(P64::Object* owner) {

        this->owner = owner;

        float buttonSetY = 200;
        float buttonSpacing = 48.0f;
        this->buttons.push_back(new GradientButton(
            "Edit Username",
            quadrant{128, buttonSetY, 256, 32},
            buttonScheme{RGBA32(25, 25, 25, 125), RGBA32(125, 125, 255, 200), EEPROM_GAME::CurUserSettings.gameFont},

            [this]() {
                if(this->keyboard  == nullptr) {
                    this->keyboard = new Keyboard("Enter Username", EEPROM_GAME::CurUserSettings.gameFont, "Username", 16);

                    this->keyboard->onEnterCallback = [this](std::string input) {
                        
  
                        std::snprintf(
                            controllerpak::CachedPlayerData[0].username,
                            CPAK_USERNAME_SIZE,
                            "%s",
                            input.c_str()
                        );


                        debugf("NEW USERNAME: %s\n", controllerpak::CachedPlayerData[0].username);
                        int result = controllerpak::fullSaveToPak(controllerpak::CachedPlayerData[0], 1);
                        delete this->keyboard;
                        this->keyboard = nullptr;

                        if(result == 1) {
                        debugf("USERNAME REGISTERED: %s\n", controllerpak::readPlayerData(1).username);
                        }
                    };
                }
            }
        ));

        this->buttons.push_back(new GradientButton(
            "Skills",
            quadrant{128, buttonSetY + buttonSpacing, 256, 32},
            buttonScheme{RGBA32(25, 25, 25, 125), RGBA32(125, 125, 255, 200), EEPROM_GAME::CurUserSettings.gameFont},

            [this]() {
                // Skills
            }
        ));

                this->buttons.push_back(new GradientButton(
            "Back",
            quadrant{128, buttonSetY + buttonSpacing * 2, 256, 32},
            buttonScheme{RGBA32(25, 25, 25, 125), RGBA32(125, 125, 255, 200), EEPROM_GAME::CurUserSettings.gameFont},

            [this]() {
                if(this != nullptr) {
                P64::SceneManager::getCurrent().sendEvent(this->owner->id, this->owner->id, 0, 0);
                }
            }
        ));


    this->xpBar = new UI::XPBar(1, quadrant{32, 32, 240, 32}, 1);
    }



  UserMenu::~UserMenu() = default;

    void UserMenu::Draw(float deltaTime) {

    if(this->xpBar != nullptr) {
        this->xpBar->draw(deltaTime);
    }

    if(this->keyboard != nullptr) {
        this->keyboard->draw(deltaTime);
        return;
    }
    
    for(int i = 0; i < (int)buttons.size(); ++i) {
        buttons[i]->isHovered = (i == curSelection);
        
        buttons[i]->draw(deltaTime);
    }

            rdpq_textparms_t TEXT_BUTTON{
          .width = 256,
        .align = ALIGN_CENTER,
        .disable_aa_fix = false
        };
        
    rdpq_text_printf(&TEXT_BUTTON, fonts::getFont(EEPROM_GAME::CurUserSettings.gameFont, 2, 1), 312, 100, "%s",
        controllerpak::CachedPlayerData[0].username);

    
    }


    void UserMenu::Update(float deltaTime) {

        joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);

        if(keyboard != nullptr) {
            keyboard->update(deltaTime);
        }

        this->mainInput = (keyboard == nullptr && warningPopup == nullptr);

        if(this->mainInput) {

            if(warningPopup != nullptr && warningPopup->closeRequest) {
                delete warningPopup;
                warningPopup = nullptr;
            }

            if(presButtons.c_down) {
                curSelection = (curSelection + 1) % (int)this->buttons.size();
            }
            if(presButtons.c_up) {
                curSelection = (curSelection - 1 + (int)this->buttons.size()) % (int)this->buttons.size();
            }

            if(presButtons.a) {

                buttons[curSelection]->Enter();

            }
        }
    }
}