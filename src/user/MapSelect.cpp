#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "../p64/assetTable.h"
#include <libdragon.h>



namespace P64::Script::CE723306229A98AC
{
  P64_DATA(
    [[P64::Name("Fade")]]
    ObjectRef Fade;
    AssetRef<sprite_t> bgSpr;
    uint8_t selectedMap = 0;
    // Put your arguments and runtime values bound to an object here.
    // If you need them to show up in the editor, add a [[P64::Name("...")]] attribute.
    //
    // Types that can be set in the editor:
    // - uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t
    // - float
    // - AssetRef<sprite_t>
    // - ObjectRef
    //
    // For unsigned integers (uint8_t/uint16_t/uint32_t) you can add a
    // [[P64::Bitmask("0=Fire, 1=Water, 2=Earth")]] attribute to edit them as a
    // named multi-select of bits instead of a plain number.
    //
    // Other types can be used but are not exposed in the editor.
  );

  // The following functions are called by the engine at different points in the object's lifecycle.
  // If you don't need a specific function you can remove it.

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

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
    // this is called on the fixed physics timestep before collision/physics are stepped
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    DrawLayer::use2D();

    
      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
              rdpq_blitparms_s bgParm = {};
    bgParm.scale_x = 512;
    bgParm.scale_y = 512;

      rdpq_textparms_t titleParms = {};
      titleParms.height = 100;

    rdpq_set_prim_color(RGBA16(0, 0, 0, 1));
    rdpq_sprite_blit(data->bgSpr.ptr, 0, 0, &bgParm);
    // this is called once every frame, and for every active camera.
    // Put your drawing code here
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

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
    // collision callbacks, only used if any collider is attached
  }
}
