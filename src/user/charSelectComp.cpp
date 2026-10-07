#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "UI/previewChar.h"
#include "Globals/players.h"
#include "Globals/gameplay.h"
#include "UI/CharSelect.h"

namespace P64::Script::CABFFBFAEEEB8D0A
{
  P64_DATA(
    //This class and object exists because P64_DATA does not handle vectors well and causes misalignment,
    // so we need to move that memory elsewhere. 

//The camera that simply exists so the scene can run without error at the first frame. In reality we won't be needing it.
      UI::CharSelect* dummyCharSelect;
    [[P64::Name("Placehold Camera")]]
    ObjectRef placeholderCamera;

  );


  void init(Object& obj, Data *data)
  {
    data->dummyCharSelect = new UI::CharSelect(obj, data->placeholderCamera);
    //Creating the previewCharacter objects 
    /*
    for(int i=0; i < players::portCount; i++) {
      
      uint16_t objId = SceneManager::getCurrent().addObject("PreviewCharacter.pf"_asset);
      data->dummyCharSelect->deferredChars.push_back(objId);
      //data->deferredChars.push_back(objId);
    }
    */

  }

  void destroy(Object& obj, Data *data)
  {
    delete data->dummyCharSelect;
    data->dummyCharSelect = nullptr;
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
  /*
for (size_t i = 0; i < data->dummyCharSelect->deferredChars.size();) {
    Object* object =
    SceneManager::getCurrent().getObjectById(data->dummyCharSelect->deferredChars[i]);

    if (!object) {
        ++i;
        continue;
    }

    data->dummyCharSelect->prevChars.emplace_back(
        static_cast<int8_t>(++Gameplay::CurrentPortCount),
        object
    );

    data->dummyCharSelect->deferredChars.erase(data->dummyCharSelect->deferredChars.begin() + i);
  */
    data->dummyCharSelect->update(obj, deltaTime);

}

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {

    data->dummyCharSelect->draw(deltaTime);
  }

}
