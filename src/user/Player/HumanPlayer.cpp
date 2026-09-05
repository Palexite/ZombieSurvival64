#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "globals/gameplay.h"
#include "globals/global.h"
#include "string"
#include "scene/components/charBody.h"
#include "scene/components/animModel.h"
#include "scene/components/Camera.h"
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
    // 1 - CameraSpawned,
    uint8_t setupFlags = 0;
    AssetRef<sprite_t> hpBar;

    Comp::AnimModel *animModel; 
    Comp::Camera *camera;
    Comp::CharBody *charBody; 

    Comp::AnimModel *HandModel;
  );



  void init(Object& obj, Data *data)
  { 
    HumanInfo hi = {};
    hi.HP = 100;
    hi.BA = 0;
    hi.CurrentItem = 0;
    hi.isDead = false;
    hi.moveSpeed = 100;
    hi.PortNumber = Gameplay::CurrentPortCount += 1;
    
    Gameplay::humansInfo.insert({obj.id, hi});
    data->Vars = &Gameplay::humansInfo.at(obj.id);

        data->animModel = obj.getComponent<Comp::AnimModel>(0);
    data->charBody = obj.getComponent<Comp::CharBody>();
    data->camera = obj.getComponent<Comp::Camera>();

// Setting up screen space for us depending on the number of ports selected



    if(User::portCount == 1) {
      data->ScreenW = 640;
      data->ScreenH = 480;
    } else if(User::portCount == 2) {
      data->ScreenH = 480;
      data->ScreenW = 320;
    } else if(User::portCount == 3 || User::portCount == 4) {
      data->ScreenH = 240;
      data->ScreenW = 320;
    }

    sprite_t *hpBarTex = (sprite_t*)AssetManager::getByIndex("tex/white.sprite"_asset);
    data->hpBar.ptr = hpBarTex;

    // initialization, this is called once when the object spawns
  }

  void destroy(Object& obj, Data *data)
  {
    // clean-up, this is called when the object gets deleted
  }


  void InputUpdates(Object& obj, Data *data, float deltaTime) {
//data->Vars->PortNumber
    joypad_buttons_t buttons = joypad_get_buttons_held(static_cast<joypad_port_t>(0));

              fm_vec3_t Axis = fm_vec3_t({0, 1, 0});
         fm_quat_t newRot = fm_quat_t({obj.rot.x, obj.rot.y, obj.rot.z, obj.rot.w});

fm_vec3_t inputVel = fm_vec3_t({0, 0, 0});
    if(buttons.c_up) {
          inputVel += (obj.rot * fm_vec3_t{0, 0, -1});
    } 
    
    if(buttons.c_right) {
          //inputVel += (obj.rot * fm_vec3_t{-1, 0, 0});
          fm_quat_rotate(&obj.rot, &newRot, &Axis, -1 * deltaTime);
    } 

    if(buttons.c_down) {
          inputVel += (obj.rot * fm_vec3_t{0, 0, 1});
          
    }  else if(buttons.c_left) {
          //inputVel += (obj.rot * fm_vec3_t{1, 0, 0});

          

          fm_quat_rotate(&obj.rot, &newRot, &Axis, 1 * deltaTime);
    }


          data->charBody->getBody().inputVelocity = inputVel;
          data->charBody->getBody().moveAndSlide(deltaTime);
  }




  void update(Object& obj, Data *data, float deltaTime)
  {
    InputUpdates(obj, data, deltaTime);
    auto viewOff = fm_vec3_t({0, 120, 0});
      data->camera->camera.setPosRot(viewOff + obj.pos, obj.rot);
  }

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
    if(!data->setupFlags) {
      
    }
    // this is called on the fixed physics timestep before collision/physics are stepped
  }

    void DrawHealthBar(Object& obj, Data *data, float deltaTime) {
          char hp_str[6];
      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
              rdpq_set_prim_color(RGBA32(200, 25, 25, 128));

        snprintf(hp_str, sizeof(hp_str), "%u", (unsigned)data->Vars->HP);
          rdpq_text_print(

            &TEXT_HEALTH, 
                1,
            data->ScreenX + data->ScreenW * 0.005, 
            data->ScreenY + (data->ScreenH * 0.95), 
            hp_str);

      rdpq_blitparms_s hpBarParm = {};
      hpBarParm.tile = TILE0;
      hpBarParm.scale_x = data->ScreenW * 0.3;
      hpBarParm.scale_y = data->ScreenH * 0.04;


    rdpq_sprite_blit(data->hpBar.ptr, 
      data->ScreenX + data->ScreenW * 0.15,
      data->ScreenY + data->ScreenH * 0.91, &
      hpBarParm);
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    if(data != nullptr) {
    DrawLayer::use2D();
    DrawHealthBar(obj, data, deltaTime);
    
        DrawLayer::useDefault();


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
