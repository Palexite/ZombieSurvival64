#include "CharSelectCorner.h"
#include "Globals/players.h"
#include "Globals/global.h"
#include "utility/splitscreen.h"
#include "utility/eeprom.h"
#include "utility/fonts.h"

namespace UI {
    CharSelectCorner::CharSelectCorner(int portId, P64::Object* previewCharacter) {
      this->portId = portId;
      this->PreviewCharacter = previewCharacter;


      this->bounds = splitscreen::calculateDimensions(portId, players::portCount);
      this->smallFontID = fonts::getFont(EEPROM_GAME::CurUserSettings.gameFont, 2, players::portCount);
      this->pData = &controllerpak::CachedPlayerData[portId];


      std::vector<std::string> charOptions = {};
        debugf("Initializings\n\n\n");
      for(data::characters::charDef& character : data::characters::charsDefined) {
        charOptions.push_back(character.name);
        debugf("Initializing character select option: %s\n", character.name.c_str());
      }
      this->charSelectPlate = new UI::SwitchPlate({64, 128, 0, 0},this->smallFontID, charOptions, NULL, this->bounds.w / 4);
          this->charSelectPlate->onSelect = [this](int selectedChar) {
            this->ChangeCharacter(selectedChar);
              P64::SceneManager::load(data::maps::mapsDefined[P64::User::mapSelected].scene);
              debugf("Loading scene %d\n", data::maps::mapsDefined[P64::User::mapSelected].scene);
          };
    }

  CharSelectCorner::~CharSelectCorner() = default;



  void CharSelectCorner::draw(float deltaTime) {
    printf("Drawing\n");
    rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
        rdpq_textparms_t TEXT_NAME{
        .align = ALIGN_LEFT,
        .valign = VALIGN_CENTER,
        .disable_aa_fix = false
        };
      

      if(this->pData != nullptr && this->pData->username[0] != '\0') {
        rdpq_text_printf(&TEXT_NAME, 
          smallFontID, 
          bounds.x + bounds.w/2 - 64,
          bounds.y + bounds.h/4,
          pData->username);

      } else {

        rdpq_text_printf(&TEXT_NAME,
          smallFontID, 
          bounds.x + bounds.w/2 - 64,
          bounds.y + bounds.h/4, 
          "Player %d", 
          portId);
      }

    if(this->charSelectPlate != nullptr) {
      this->charSelectPlate->draw(deltaTime);
    } 


  }

  void CharSelectCorner::ChangeCharacter(int charId) {

  }

  void CharSelectCorner::update(float deltaTime) {
    joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    if(presButtons.a) {
      debugf("A pressed\n");
      //P64::SceneManager::load(data::maps::mapsDefined[P64::User::mapSelected].scene);
    }
    
    if(this->colorPicker != nullptr) {
      this->colorPicker->update(deltaTime);
    }
      
    if(this->charSelectPlate != nullptr) {
      this->charSelectPlate->update(deltaTime);
    }


  }
}