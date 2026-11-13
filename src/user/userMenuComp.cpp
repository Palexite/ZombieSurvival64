#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "UI/Popup.h"
#include "UI/UserMenu.h"
#include "string.h"

#include "utility/controllerpak.h"
#include "utility/eeprom.h"
namespace P64::Script::C68F5512B2D72F6C
{

  P64_DATA(
          [[P64::Name("main Menu")]]
    ObjectRef mainMenu;
        Popup *popup = nullptr; 
        UI::UserMenu *userMenu = nullptr;
  );


  void init(Object& obj, Data *data)
  {
    debugf("userMenu: %p\n", static_cast<void*>(data->userMenu));
    data->popup = nullptr;
    data->userMenu = nullptr;
    data->mainMenu->setEnabled(false);
  }



  void destroy(Object& obj, Data *data)
  {
    if(data->userMenu != nullptr) {
    data->userMenu->~UserMenu();
    data->userMenu = nullptr;
    }
  }



  void update(Object& obj, Data *data, float deltaTime)
  {

    if(data->popup) {
      data->popup->update(deltaTime);
    } else {

      if(data->userMenu) {
        data->userMenu->Update(deltaTime);
      }
    }
  }


  void draw(Object& obj, Data *data, float deltaTime)
  {


    DrawLayer::use2D();
    
        if(data->popup && data->popup->closeRequest)
        {
            delete data->popup;
            data->popup = nullptr;
        }
        if(data->popup) {
            data->popup->draw(deltaTime);
        }

        if(data->userMenu) {
            data->userMenu->Draw(deltaTime);
        }
      
    DrawLayer::useDefault();
  }



  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {

    switch(event.type)
    {
      case EVENT_TYPE_ENABLE:
        SceneManager::getCurrent().sendEvent(obj.id, obj.id, EVENT_TYPE_CUSTOM_START, 1);
      break;

      case EVENT_TYPE_CUSTOM_START:

      if(event.value == 0) {
        obj.setEnabled(false);
        data->mainMenu->setEnabled(true);


      } else if(event.value == 1) {

        if(controllerpak::portHasCPak(JOYPAD_PORT_1)) {
          int result = controllerpak::mountCPak(1);

          debugf("result: %d\n", result);
          data->userMenu = new UI::UserMenu(&obj);
          /*
          if(controllerpak::readPlayerData(1) == nullptr) {
            controllerpak::FormatPlayerData(1);
          }
          */
        } else {


          std::vector<std::string> choices = {"RETURN", "RETRY"};

          const uint16_t objectId = obj.id;



          auto dumbyCallback = [](int choice)  {
          };

          data->popup = new Popup(48, 32, 640, 480, "No Controller Pak Detected", 
          "You need a controller pak to enter. Please check that it is mounted properly and that the controller is plugged into the LEFT-MOST port.", 
          RGBA32(0, 0, 0, 125), 
          EEPROM_GAME::CurUserSettings.gameFont, 
          choices,
          dumbyCallback, 
          &obj);


          // The callback needs to be defined later, since it references the newly created Popup.

          data->popup->choiceCallback = [objectId = obj.id, popup = data->popup]
          (int choice) {

          if(choice == 0) {

            SceneManager::getCurrent().sendEvent(objectId, objectId, EVENT_TYPE_CUSTOM_START, 0);
            popup->Close();
          } else if(choice == 1) {

            popup->Close();
            SceneManager::getCurrent().sendEvent(objectId, objectId, EVENT_TYPE_CUSTOM_START, 1);
            }

          };

        }
      }
    }
  }
}
