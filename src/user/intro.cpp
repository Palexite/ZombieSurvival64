#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "scene/components/camera.h"
#include "utility/math.h"

namespace P64::Script::CDABF08077359657
{
     rdpq_textparms_t TEXT_CENTER{
      .width = 256,
      .align = ALIGN_CENTER,
      .disable_aa_fix = true
    };

  P64_DATA(
    [[P64::Name("Orbital Camera")]]
    ObjectRef Camera;
        [[P64::Name("Object To Orbit")]]
    ObjectRef orbitObj;
        [[P64::Name("Character 1")]]
    ObjectRef char1;
        [[P64::Name("Character 2")]]
    ObjectRef char2;
        [[P64::Name("Character 3")]]
    ObjectRef char3;
        [[P64::Name("Character 4")]]
    ObjectRef char4;
      [[P64::Name("Divider")]]
    ObjectRef divider;

    int Scenario = 0;
  );



  void init(Object& obj, Data *data)
  {
    // initialization, this is called once when the object spawns
      
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    // this is called once every frame, put your main logic here
          //fm_vec3_t Axis = fm_vec3_t({0, 1, 0});
        // fm_quat_t newRot = fm_quat_t({obj.rot.x, obj.rot.y, obj.rot.z, obj.rot.w});
          Comp::Camera *cam = data->Camera.get()->getComponent<Comp::Camera>();


          //Make the camera orbit around the focused object.
          fm_quat_t camRot = Math_Extended::LookAt( data->Camera.get()->pos,data->orbitObj.get()->pos);
          data->Camera.get()->rot = camRot;
     data->Camera.get()->pos += camRot * fm_vec3_t{128, 0, 0} * deltaTime;
      
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
           DrawLayer::use2D();


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
