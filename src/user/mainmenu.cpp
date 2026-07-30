#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "../p64/assetTable.h"
#include <libdragon.h>
#include <scene/components/code.h>

namespace P64::Script::C4D5BD79BCFCAECC


{

        rdpq_textparms_t TEXT_BUTTON{
        .width = 70,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true
    };

            rdpq_textparms_t TEXT_SUB{
        .width = 120,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true
    };


  P64_DATA(
    AssetRef<sprite_t> buttonSpr;
    AssetRef<sprite_t> logoSpr;

    [[P64::Name("player Select")]]
    ObjectRef playerSel;

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
    // clean-up, this is called when the object gets deleted
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);

if(presButtons.a == 1) {
  AudioManager::play2D("sfx/ui/press1.wav64"_asset);
  SceneManager::getCurrent().sendEvent(obj.id, obj.id, 0, data->selected);

        Scene &r = SceneManager::getCurrent();
        Object *pSel = data->playerSel.get();
        //void *d = pSel->getComponent<Comp::CollBody>()->collider.id
          pSel->setEnabled(true);
        obj.setEnabled(false);


  //r.getObjectById()
} else if(presButtons.c_up || presButtons.c_left) {
AudioManager::play2D("sfx/ui/hover1.wav64"_asset);
      if(data->selected <= 0) {
        data->selected = 2;
      } else {
        data->selected -= 1;
      }
} else if(presButtons.c_down || presButtons.c_right) {
AudioManager::play2D("sfx/ui/hover1.wav64"_asset);
      if(data->selected >= 2) {
        data->selected = 0;
      } else {
        data->selected += 1;
      }
}



  }

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
    // this is called on the fixed physics timestep before collision/physics are stepped
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    DrawLayer::use2D();
          rdpq_blitparms_s logoblitParm = {};
          //blitParm.tile = TILE1;
          logoblitParm.scale_y = 1.5;
          logoblitParm.scale_x = 1.5;

          rdpq_sprite_blit(data->logoSpr.ptr, 12, 80, &logoblitParm);
          rdpq_text_printf(&TEXT_SUB, 1, 48, 140, "- N64 EDITION -");
      constexpr const char* selection[3]  = {
        "Play",
        "Settings",
        "Credits"
      };
          rdpq_blitparms_s blitParm = {};
          //blitParm.tile = TILE1;
          blitParm.scale_y = 16;
          blitParm.scale_x = 1;
        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);


      rdpq_textparms_t titleParms = {};
      titleParms.height = 100;
      for(int i = 0; i < 3; i++) {

          if(i == data->selected) {
          rdpq_set_prim_color(RGBA32(128, 128, 255, 255));
          } else {
            rdpq_set_prim_color(RGBA32(0, 0, 0, 255));
          }
          rdpq_sprite_blit(data->buttonSpr.ptr, 16 + i * 48, 180 + (i * 16), &blitParm);

          if(i == data->selected) {
              //char *s = (char*)"^01";
              // char *concat = strcat(s,  selection[i]);
          //rdpq_text_printf(&TEXT_BUTTON, 1, 19 + i * 48, 180 + i * 16, concat);
          }
          rdpq_text_printf(&TEXT_BUTTON, 1, 16 + i * 48, 180 + i * 24, selection[i]);



      }
    DrawLayer::useDefault();
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
    // generic events an object can receive
    switch(event.type)
    {
      case EVENT_TYPE_READY: // object is fully initialized, no update call has happened yet
      break;
      case EVENT_TYPE_ENABLE: // object got enabled
      break;
      case EVENT_TYPE_DISABLE: // object got disabled
      break;
      case EVENT_TYPE_CUSTOM_START:
      break;
        /*
      switch(event.value) {
        case 0:

        Scene &r = SceneManager::getCurrent();
        Object *pSel = data->playerSel.get();
          pSel->setEnabled(true);
        obj.setEnabled(false);
        break;

      }
      */
      // you can check for your own custom types here too
    }
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
    // collision callbacks, only used if any collider is attached
  }
}
