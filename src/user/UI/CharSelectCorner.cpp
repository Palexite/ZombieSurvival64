#include "CharSelectCorner.h"
#include "Globals/players.h"

#include "utility/splitscreen.h"
#include "utility/eeprom.h"
#include "utility/fonts.h"

namespace UI {
    void drawCharSelect();
    CharSelectCorner::CharSelectCorner(int portId, P64::Object* previewCharacter) {
      this->portId = portId;
      this->PreviewCharacter = previewCharacter;


      this->bounds = splitscreen::calculateDimensions(portId, players::portCount);
      this->smallFontID = fonts::getFont(EEPROM_GAME::CurUserSettings.gameFont, 2, players::portCount);
      this->pData = &controllerpak::CachedPlayerData[portId];
    }

  CharSelectCorner::~CharSelectCorner() = default;



  void CharSelectCorner::draw(float deltaTime) {

    rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
        rdpq_textparms_t TEXT_NAME{
        .width = 320,
        .align = ALIGN_CENTER,
        .disable_aa_fix = false
        };
      

      if(this->pData != nullptr && this->pData->username[0] != '\0') {
        rdpq_text_printf(&TEXT_NAME, 
          smallFontID, 
          bounds.x + bounds.w/2,
          bounds.y + 64, 
          pData->username);

      } else {

        rdpq_text_printf(&TEXT_NAME, 
          smallFontID, 
          bounds.x + 64, 
          bounds.y + 64, 
          "Player %d", 
          portId);
      }
    if(this->colorPicker != nullptr) {
      this->colorPicker->draw(deltaTime);
    }

  }

  void CharSelectCorner::ChangeCharacter(int charId) {

  }

  void CharSelectCorner::update(float deltaTime) {
    /*
    if(this->colorPicker != nullptr) {
      this->colorPicker->update(deltaTime);
    }
      */
  }
}