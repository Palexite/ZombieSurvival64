#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "UI/previewChar.h"
#include "Globals/players.h"
#include "Globals/game.h"
#include "UI/CharSelect.h"

namespace P64::Script::CABFFBFAEEEB8D0A
{
  P64_DATA(
    //This class and object exists because P64_DATA does not handle vectors well and causes misalignment,
    // so we need to move that memory elsewhere. 

//The camera that simply exists so the scene can run without error at the first frame. In reality we won't be needing it.
    [[P64::Name("Placehold Camera")]]
    ObjectRef placeholderCamera;
    
      UI::CharSelect* dummyCharSelect;

  );


  void init(Object& obj, Data *data)
  {
    data->dummyCharSelect = nullptr;
    data->dummyCharSelect = new UI::CharSelect(obj, data->placeholderCamera);

  }

  void destroy(Object& obj, Data *data)
  {
    delete data->dummyCharSelect;
    data->dummyCharSelect = nullptr;
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    data->dummyCharSelect->update(obj, deltaTime);

}

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    DrawLayer::use2D();
      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);

    data->dummyCharSelect->draw(deltaTime);
    DrawLayer::useDefault();
  }

}
