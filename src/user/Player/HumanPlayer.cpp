#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "gameplay.h"
#include "global.h"
#include "string"
#include <stdint.h>

namespace P64::Script::CD3F67733C77127D
{


          rdpq_textparms_t TEXT_HEALTH{
        .width = 128,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true
    };

  P64_DATA(

    HumanInfo *Vars;

    // For UI and splitscreen
    float ScreenW = 640;
    float ScreenH = 480;
    float ScreenX = 0;
    float ScreenY = 0;

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
    HumanInfo hi = {};
    hi.HP = 100;
    hi.BA = 0;
    hi.CurrentItem = 0;
    hi.isDead = false;
    hi.moveSpeed = 100;
    hi.PortNumber =  Gameplay::CurrentPortCount += 1;
    
    Gameplay::humansInfo.insert({obj.id, hi});
    data->Vars = &Gameplay::humansInfo.at(obj.id);
    
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

    void DrawHealthBar(Object& obj, Data *data, float deltaTime) {


          char hp_str[6];
        snprintf(hp_str, sizeof(hp_str), "%u", (unsigned)data->Vars->HP);

          rdpq_text_print(

            &TEXT_HEALTH, 
                1,

            data->ScreenX + 25, 
            data->ScreenY + 25, 

            //(char*)(uintptr_t)(data->Vars->HP));
            hp_str);
    
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    if(data != nullptr) {
    DrawLayer::use2D();
      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);

    DrawHealthBar(obj, data, deltaTime);
    // this is called once every frame, and for every active camera.
    // Put your drawing code here
    }
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
