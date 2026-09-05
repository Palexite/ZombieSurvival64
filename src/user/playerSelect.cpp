#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "../p64/assetTable.h"
#include "globals/global.h"
#include <libdragon.h>

namespace P64::Script::C7E952F114A8850F
{

        rdpq_textparms_t TEXT_BUTTON{
        .width = 90,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true
    };


            rdpq_textparms_t TEXT_TITLE{
        .width = 256,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true
    };
  P64_DATA(

    [[P64::Name("Main Menu")]]
    ObjectRef mainMenu;

    [[P64::Name("Map Select")]]
    ObjectRef mapSelect;
    uint8_t selected = 0;
        uint8_t Xselected = 1;
    float yBuffer = -128;
    uint8_t shouldOpen = 0;
    AssetRef<sprite_t> bgSpr;

    AssetRef<sprite_t> buttonSpr;

    AssetRef<sprite_t> plyIcon;

  );



  void init(Object& obj, Data *data)
  {
    // initialization, this is called once when the object spawns
      data->bgSpr.ptr = (sprite_t*)AssetManager::getByIndex("tex/white.sprite"_asset);
      data->buttonSpr.ptr = (sprite_t*)AssetManager::getByIndex("tex/grad1.sprite"_asset);
      data->yBuffer = -128;


  }

  void destroy(Object& obj, Data *data)
  {
    // clean-up, this is called when the object gets deleted
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    if(data->shouldOpen == 0) {
      if(data->yBuffer < 120) {
      data->yBuffer += 8;
      }
    } else {
            data->yBuffer -= 8;
            if(data->yBuffer <= -127) {
              obj.setEnabled(false);
            }
    }
    

joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    if(presButtons.a == 1) {
      SceneManager::getCurrent().sendEvent(obj.id, obj.id, 0, 0);

  AudioManager::play2D("sfx/ui/press1.wav64"_asset);




} else if(presButtons.c_up ) {
AudioManager::play2D("sfx/ui/hover1.wav64"_asset);
      if(data->selected <= 0) {
        data->selected = 3;
      } else {
        data->selected -= 1;
      }


} else if(presButtons.c_down) {
AudioManager::play2D("sfx/ui/hover1.wav64"_asset);
      if(data->selected >= 3) {
        data->selected = 0;
      } else {
        data->selected += 1;
      }


} else if(presButtons.c_right) {
  data->Xselected = 1;
} else if(presButtons.c_left) {
  data->Xselected = 0;
}

    // this is called once every frame, put your main logic here
  }

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
    // this is called on the fixed physics timestep before collision/physics are stepped
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {

DrawLayer::use2D();

      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
    // this is called once every frame, and for every active camera.
    // Put your drawing code here
    rdpq_text_printf(&TEXT_TITLE, 1, 86, data->yBuffer - 4, "PLAYER COUNT");
      constexpr const char* selection[4]  = {
        "Solo",
        "Duo",
        "Trio",
        "Quad",
      };

          rdpq_blitparms_s buttonParm = {};
    buttonParm.scale_x = 1;
    buttonParm.scale_y = 32;
    buttonParm.flip_x = true;

              rdpq_blitparms_s exitParm = {};
    exitParm.scale_x = 0.5;
    exitParm.scale_y = 24;


              rdpq_blitparms_s bgParm = {};
    bgParm.scale_x = 512;
    bgParm.scale_y = 256;
rdpq_set_prim_color(RGBA32(0, 0, 0, 128));
rdpq_sprite_blit(data->bgSpr.ptr, 30, data->yBuffer, &bgParm);

    for(int i = 0; i < 4; i++) {



    if(data->selected == i && (data->Xselected == 1)) {
    rdpq_set_prim_color(RGBA32(0, 0, 125, 128));

    } else {
    rdpq_set_prim_color(RGBA32(0, 0, 0, 128));
    }

// Drawing buttons //

    rdpq_sprite_blit(data->buttonSpr.ptr, 
      30 + bgParm.scale_x * .8, 
      (i * 32) + data->yBuffer,
       &buttonParm);
       
    rdpq_text_printf(&TEXT_BUTTON, 
      1, 
      30 + bgParm.scale_x * .8, 
      16 + i * 32 + data->yBuffer, 
      selection[i]);
    }

    if(data->Xselected == 0) {
          rdpq_set_prim_color(RGBA32(0, 0, 125, 128));
    } else {
              rdpq_set_prim_color(RGBA32(0, 0, 0, 128));
    }

      rdpq_sprite_blit(data->buttonSpr.ptr, 32, 0 + data->yBuffer, &exitParm);
      rdpq_text_printf(&TEXT_BUTTON, 1, 32, 16 + data->yBuffer, "Back");
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
            data->shouldOpen = 0;
      break;
      case EVENT_TYPE_DISABLE: // object got disabled
      break;
      case EVENT_TYPE_CUSTOM_START:
      

      if(data->Xselected == 1) {
      //User::portCount = data->selected;
        data->shouldOpen = 1;

        Scene &r = SceneManager::getCurrent();
        Object *mSel = data->mapSelect.get();

          mSel->setEnabled(true);
      } else {
        data->shouldOpen = 1;
        data->mainMenu.get()->setEnabled(true);
      }
      
      break;

      // you can check for your own custom types here too
    }
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
    // collision callbacks, only used if any collider is attached
  }
}
