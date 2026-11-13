#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "../p64/assetTable.h"
#include <libdragon.h>
#include <scene/components/code.h>
#include "UI/Popup.h"

#include "utility/fonts.h"
#include "utility/eeprom.h"

namespace P64::Script::C4D5BD79BCFCAECC
{
        rdpq_textparms_t TEXT_BUTTON{
        .width = 200,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true
    };

            rdpq_textparms_t TEXT_SUB{
        .width = 320,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true
    };


  P64_DATA(

    AssetRef<sprite_t> buttonSpr;
    AssetRef<sprite_t> logoSpr;

    [[P64::Name("player Select")]]
    ObjectRef playerSel;

    [[P64::Name("user Menu")]]
    ObjectRef userMenu;

    uint8_t selected = 0;
  );



  void init(Object& obj, Data *data)
  {

        sprite_t *spTex = (sprite_t*)AssetManager::getByIndex("tex/grad1.sprite"_asset);
    data->buttonSpr.ptr = spTex;

            sprite_t *logoTex = (sprite_t*)AssetManager::getByIndex("tex/zslogo.sprite"_asset);
    data->logoSpr.ptr = logoTex;
  }

  void destroy(Object& obj, Data *data)
  {
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);

if(presButtons.a == 1) {
  AudioManager::play2D("sfx/ui/press1.wav64"_asset);
  SceneManager::getCurrent().sendEvent(obj.id, obj.id, EVENT_TYPE_CUSTOM_START, data->selected);


} else if(presButtons.c_up || presButtons.c_left) {
AudioManager::play2D("sfx/ui/hover1.wav64"_asset);
      if(data->selected <= 0) {
        data->selected = 3;
      } else {
        data->selected -= 1;
      }
} else if(presButtons.c_down || presButtons.c_right) {
AudioManager::play2D("sfx/ui/hover1.wav64"_asset);
      if(data->selected >= 3) {
        data->selected = 0;
      } else {
        data->selected += 1;
      }
}
  }

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
    
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    DrawLayer::use2D();
            rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
          rdpq_blitparms_s logoblitParm = {};
          logoblitParm.scale_y = 2;
          logoblitParm.scale_x = 2;
          
          rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
          rdpq_sprite_blit(data->logoSpr.ptr, 12, 80, &logoblitParm);
          rdpq_text_printf(&TEXT_SUB, 2, -20, 160, "- N64 EDITION -");
          
      constexpr const char* selection[4]  = {
        "Play",
        "Player Menu",
        "Settings",
        "Credits"
      };

          rdpq_blitparms_s blitParm = {};
          blitParm.scale_y = 32;
          blitParm.scale_x = 2;


      rdpq_textparms_t titleParms = {};
      titleParms.height = 100;
      for(int i = 0; i < 4; i++) {

        if(i == data->selected) {
          rdpq_set_prim_color(RGBA32(128, 128, 255, 255));
        } else {
            rdpq_set_prim_color(RGBA32(0, 0, 0, 255));
        }
        rdpq_sprite_blit(data->buttonSpr.ptr, 16 + i * 48, 300 + (i * 32), &blitParm);

        rdpq_text_printf(&TEXT_BUTTON, 
          fonts::getFont(EEPROM_GAME::CurUserSettings.gameFont, FONTSIZE_SMALL, 1),
          16 + i * 48, 
          320 + i * 32, 
          selection[i]);
      }


    DrawLayer::useDefault();
  }

  void popChoice(int choice) {
    
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
    // generic events an object can receive
    switch(event.type)
    {
      case EVENT_TYPE_CUSTOM_START:
      switch(event.value) {
          case 0:
            data->playerSel.get()->setEnabled(true);
            obj.setEnabled(false);
            break;
          case 1:
          data->userMenu.get()->setEnabled(true);
          obj.setEnabled(false);
            break;
        
      }
      break;
    }
  }
}
