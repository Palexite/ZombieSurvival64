#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "../p64/assetTable.h"
#include <libdragon.h>



namespace P64::Script::CE723306229A98AC
{

              rdpq_textparms_t TEXT_TITLE{
        .width = 256,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true

              };
  P64_DATA(
    AssetRef<sprite_t> bgSpr;
    uint8_t selectedMap = 0;

  );


  void init(Object& obj, Data *data)
  {
        sprite_t *bgTex = (sprite_t*)AssetManager::getByIndex("tex/white.sprite"_asset);
        data->bgSpr.ptr = bgTex;
    // initialization, this is called once when the object spawns
  }

  void destroy(Object& obj, Data *data)
  {
    // clean-up, this is called when the object gets deleted
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    // this is called once every frame, put your main logic here
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    DrawLayer::use2D();


      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
 
      rdpq_blitparms_s bgParm = {};
    bgParm.scale_x = 480;
    bgParm.scale_y = 240;
      rdpq_textparms_t titleParms = {};
      titleParms.height = 100;
    rdpq_set_prim_color(RGBA32(0, 64, 128, 128));


    rdpq_sprite_blit(data->bgSpr.ptr, 64, 64, &bgParm);
      rdpq_text_printf(&TEXT_TITLE, 1, 180, 48, "MAP SELECT");


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

      // you can check for your own custom types here too
    }
  }
}
