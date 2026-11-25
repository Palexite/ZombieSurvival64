#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "globals/game.h"
#include "globals/global.h"
#include "Player/HumanPlayer.h"
#include "Globals/Players.h"
#include "string"
#include "scene/components/charBody.h"
#include "scene/components/animModel.h"
#include "scene/components/Camera.h"
#include <stdint.h>


// THIS COMPONENT IS OBSOLETE AND WILL BE REMOVED SOON. DO NOT RELY ON IT.

namespace P64::Script::CD3F67733C77127D
{


          rdpq_textparms_t TEXT_HEALTH{
        .width = 128,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true
    };

  P64_DATA(
    // 1 - CameraSpawned,
    
    uint8_t setupFlags = 0;
    uint8_t portNum = 0;

    Comp::AnimModel *animModel; 
    Comp::Camera *camera;
    Comp::CharBody *charBody; 
    std::unique_ptr<Player> *localPlayer;
    Comp::AnimModel *HandModel;
  );



  void init(Object& obj, Data *data)
  { 

  }

  void destroy(Object& obj, Data *data)
  {
  }


  void InputUpdates(Object& obj, Data *data, float deltaTime) {

    joypad_buttons_t buttons = joypad_get_buttons_held(static_cast<joypad_port_t>(0));

    fm_vec3_t Axis = fm_vec3_t({0, 1, 0});
    fm_quat_t newRot = fm_quat_t({obj.rot.x, obj.rot.y, obj.rot.z, obj.rot.w});

    fm_vec3_t inputVel = fm_vec3_t({0, 0, 0});
    if(buttons.c_up) {


          inputVel += (obj.rot * fm_vec3_t{0, 0, -1});
    } 
    
    if(buttons.c_right) {

          fm_quat_rotate(&obj.rot, &newRot, &Axis, -1 * deltaTime);

    } 

    if(buttons.c_down) {

          inputVel += (obj.rot * fm_vec3_t{0, 0, 1});
          
    }  else if(buttons.c_left) {

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
  }


  void draw(Object& obj, Data *data, float deltaTime)
  {
    if(data != nullptr) {
    DrawLayer::use2D();    
        DrawLayer::useDefault();


    }
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
    switch(event.type)
    {
      case EVENT_TYPE_READY:
      break;
      case EVENT_TYPE_ENABLE:
      break;
      case EVENT_TYPE_DISABLE:
      break;

    }
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
  }
}
