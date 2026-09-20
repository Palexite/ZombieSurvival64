#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "scene/components/camera.h"
#include "utility/math.h"
#include <algorithm>
#include "utility/fade.h"

namespace P64::Script::CDABF08077359657
{
  static constexpr const char *CREDITS[3] = {
    "Founded by William 'JetBoom' Moodhe",
    "Music Score by Austin 'Little Nemo' Killey",
    "Programmed by Peter 'Palexite' Panagopoulos",
  };

     rdpq_textparms_t TEXT_CENTER{
      .width = 768,
      .align = ALIGN_CENTER,
      .disable_aa_fix = true
    };

  P64_DATA(
    [[P64::Name("Orbital Camera")]]
    ObjectRef Camera;
        [[P64::Name("Object To Orbit")]]
    ObjectRef orbitObj;

      [[P64::Name("Main Menu")]]
    ObjectRef mainMenuObj;

      [[P64::Name("Divider")]]
    ObjectRef divider;


    // Everything cutscene related
    int chore = 0;
    int currentCredit = 0;
    float nextScenario = 4;
    float ScenarioDelta = 0;
    float camSpinSpeed = 32;
        float camLerpTime = 4;
    float camLerpDelta = 1;
    int shouldLerp = 0;

    fm_vec3_t camLerpStartPos = fm_vec3_t({0, 0, 0});
    fm_vec3_t camLerpPos = fm_vec3_t({0, 0, 0});
      UI::Fade fade;
  );



  void init(Object& obj, Data *data)
  {
      data->fade = UI::Fade(0, 0, 640, 480, 2, RGBA32(0, 0, 0, 0), false, false);
  }



  void update(Object& obj, Data *data, float deltaTime)
  {
          //fm_vec3_t Axis = fm_vec3_t({0, 1, 0});
        // fm_quat_t newRot = fm_quat_t({obj.rot.x, obj.rot.y, obj.rot.z, obj.rot.w});
          Comp::Camera *cam = data->Camera.get()->getComponent<Comp::Camera>();


          //Make the camera orbit around the focused object.
          fm_quat_t camRot = Math_Extended::LookAt( data->Camera.get()->pos,data->orbitObj.get()->pos);
          data->Camera.get()->rot = camRot;
     data->Camera.get()->pos += camRot * fm_vec3_t{data->camSpinSpeed, 0, 0} * deltaTime;
      


     // ==== For cutscene handling ====

     data->ScenarioDelta += deltaTime;

        if(data->chore == 0) {
          if(data->ScenarioDelta > data->nextScenario) {
                
                data->fade.StartFadeIn();
                data->ScenarioDelta = 0;
          }
        }
     // Check to see if we're still displaying credits. if the fade In is complete, fade out and display the next credit. 
     //when all credits are done, set the chore equal to 1 to indicate we're ready to display the title screen.

        if(data->fade.curTime >= data->fade.fadeTime && data->fade.fadeIn) {
          data->fade.StartFadeOut();

          if(data->currentCredit < 2) {
          data->currentCredit += 1;
          } else {
            data->chore = 1;
            data->mainMenuObj.get()->setEnabled(true);
            data->divider.get()->setEnabled(false);
          }
        }

        if(data->shouldLerp) {
          if(data->camLerpTime > 0.0f) {
            data->camLerpDelta += deltaTime;
            float lerpAmount = std::clamp(data->camLerpDelta / data->camLerpTime, 0.0f, 1.0f);
            fm_vec3_lerp(&data->Camera.get()->pos, &data->camLerpStartPos, &data->camLerpPos, lerpAmount);

            if(lerpAmount >= 1.0f) {
              data->shouldLerp = false;
            }
          } else {
            data->Camera.get()->pos = data->camLerpPos;
            data->shouldLerp = false;
          }
        }
  }




  void draw(Object& obj, Data *data, float deltaTime)
  {
           DrawLayer::use2D();


          // If we're presenting the credits of the game.
          if(data != nullptr && data->chore == 0 && data->currentCredit >= 0 && data->currentCredit < 3) {
            rdpq_text_print(&TEXT_CENTER, 2, -100, 360, CREDITS[data->currentCredit]);
          }
          if (data != nullptr)
          {
            data->fade.fadeDraw(deltaTime);
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
      case 4:
      if(event.value == 1) {
        fm_vec3_t offset = fm_vec3_t({0, 0, 64});
        data->camLerpStartPos = data->Camera.get()->pos;
        fm_vec3_add(&data->camLerpPos, &data->orbitObj.get()->pos, &offset);
        data->camLerpDelta = 0;
        data->shouldLerp = true;
        data->camLerpTime = 2;
      }
      break;
      // you can check for your own custom types here too
    }
  }
}
