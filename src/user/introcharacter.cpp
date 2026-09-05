#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "scene/components/animModel.h"
#include "globals/global.h"
#include <string>

namespace P64::Script::C9FEE7D78BC12ABE
{
  P64_DATA(

    Comp::AnimModel *anim;

    char CarriedItem = *"OWEN";

  );



  void init(Object& obj, Data *data)
  {
  }
  void destroy(Object& obj, Data *data)
  {
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
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
