#include "script/userScript.h"
#include "scene/sceneManager.h"
#include <algorithm>

#include "math.h"

namespace P64::Script::CE32854BD7DD9A59
{

     rdpq_textparms_t TEXT_CENTER{
      .width = 256,
      .align = ALIGN_CENTER,
      .disable_aa_fix = true
    };

  P64_DATA(
[[P64::Name("Duration")]]
  float inOutDura = 1;

  float progress = 1;

  AssetRef<sprite_t> fadeSpr;

  //[[P64::Name("Fade Sprite")]]
    //AssetRef<sprite_t> fadeSpr;

  [[P64::Name("Flags"), P64::Bitmask("0=Fade In, 1=Destroy On Out, 2=OldFadeValue")]]
  uint8_t flags;


// FLAGS - 1:fadeIn, 2:destroyOnOut, 3:OldFadeInValue

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

  void init(Object& obj, Data* data)
  {
    //obj.flags = obj.flags & (0 << 0);
    //obj.flags = obj.flags & (0 << 1);
    sprite_t *spTex = sprite_load("rom:/tex/white.sprite");
    //surface_t surfTex = sprite_get_pixels(&spTex);
    data->fadeSpr.ptr = spTex;
    //rdpq_tex_upload(TILE0, surfTex, NULL);
  }

  void destroy(Object& obj, Data* data)
  {
      // clean-up, this is called when the object gets deleted
  }

  void OnIn(Object& obj, Data* data) {
  }

  void update(Object& obj, Data* data, float deltaTime)
  {
      // this is called once every frame, put your main logic here

    bool fadeIn = data->flags & (1 << 0);
    bool destroyOnOut = data->flags & (1 << 1);
    bool oldFadeIn = data->flags & (1 << 2);

    if(fadeIn != oldFadeIn) {
        data->progress = 0;
    }

      float ratio = data->progress / data->inOutDura;
      if (!fadeIn && destroyOnOut) {
          if (ratio >= 1) {
              obj.remove();
          }
      }
      
      data->progress = std::clamp(data->progress + deltaTime, 0.0f, data->inOutDura);
      
      data->flags = data->flags | ((int)fadeIn << 2);
  }

  void fixedUpdate(Object& obj, Data* data, float fixedDeltaTime)
  {
      // this is called on the fixed physics timestep before collision/physics are stepped
  }

  void draw(Object& obj, Data* data, float deltaTime)
  {
DrawLayer::use2D();
    rdpq_blitparms_s blitParm = {};
    blitParm.tile = TILE0;
    blitParm.scale_x = 512;
    blitParm.scale_y = 512;

    bool fadeIn = data->flags & (1 << 0);
      if (fadeIn) {
              rdpq_set_prim_color(RGBA32(0, 0, 0, static_cast<uint8_t>((data->progress / data->inOutDura) * 255)));
      }
      else {
              rdpq_set_prim_color(RGBA32(0, 0, 0, static_cast<uint8_t>(( 1-data->progress / data->inOutDura) * 255)));
      }
        rdpq_sprite_blit(data->fadeSpr.ptr, 0, 0, &blitParm);
      // this is called once every frame, and for every active camera.
      // Put your drawing code here

 DrawLayer::useDefault();
  }

  void onEvent(Object& obj, Data* data, const ObjectEvent& event)
  {
      // generic events an object can receive
      switch (event.type)
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

  void onCollision(Object& obj, Data* data, const Coll::CollEvent& event)
  {
      // collision callbacks, only used if any collider is attached
  }
}
