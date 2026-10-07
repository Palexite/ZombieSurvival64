#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "utility/controllerpak.h"
#include "UI/Popup.h"
#include "string.h"
namespace P64::Script::C68F5512B2D72F6C
{
  void popChoice(int choice) {
    
  }

  P64_DATA(
    Popup *popup; 

        [[P64::Name("main Menu")]]
    ObjectRef mainMenu;
  );


  void init(Object& obj, Data *data)
  {
  }

  void destroy(Object& obj, Data *data)
  {
  }

  void update(Object& obj, Data *data, float deltaTime)
  {


  if(data->popup) {
    
  }
  }

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    if(data->popup) {
        data->popup->draw(deltaTime);
    }
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
    switch(event.type)
    {
      case EVENT_TYPE_READY:
      
      break;
      case EVENT_TYPE_ENABLE:

    if(controllerpak::portHasCPak(JOYPAD_PORT_1)) {
    } else {
               std::vector<std::string> choices = {"RETURN", "RETRY"};
      data->popup = new Popup(48, 32, 640, 480, "No Controller Pak Detected", "You need a controller pak to enter. Please check that it is mounted properly.", RGBA32(0, 0, 0, 255), 1, choices, popChoice);
      // Also possible your controller pak is corrupted and fucked lmaoooo
    }
    
      break;
      case EVENT_TYPE_DISABLE:
      break;
    }
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
    // collision callbacks, only used if any collider is attached
  }
}
