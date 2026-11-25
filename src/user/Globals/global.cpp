#include "script/globalScript.h"
#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "global.h"
#include "globals/game.h"

#include "Gamemodes/gamemode.h"

#include "utility/fonts.h"
#include "UI/Panel.h"

namespace P64::User {


  float deltaTime = 0;
  uint8_t flags = 0;
  // 1 = Human, 0 = Zombie
  uint8_t portTeam = 1;
  uint8_t mapSelected = 0;
  std::vector<std::unique_ptr<UI::Panel>> panels = {};

}


namespace P64::GlobalScript::C6EFF0964420055D
{


  void onGameInit()
  {
        data::maps::loadMaps();
        data::characters::loadCharacters();
        fonts::setupFonts();

        

    // called once when the game starts, all other systems (e.g. asset manager) are already inititalized
  }

  void onScenePreLoad()
  {
    // right before a new scene is loaded
  }

  void onScenePostLoad()
  {
    // right after a new scene was loaded, but before any update has happened yet
    if(Game::currentGamemode != nullptr) {
        Game::currentGamemode->onGameStart();
    }
  }

  void onScenePreUnload()
  {
    // right before a scene is unloaded
  }

  void onScenePostUnload()
  {
    // right after a scene was unloaded
  }

  void onSceneUpdate()
  {
    // called once per frame during the update phase of the frame.
    // this is done before all the object updates.
  }

  void onScenePreDraw()
  {
    // called once per frame during the draw phase of the frame.
    // this is done before all the object draws, *NOT* per camera, just once.
    // The default 3D layer is active and must be restored if changed.
  }

  void onScenePreDraw3D()
  {

    // called once per frame per camera.
    // this is done before all object draws for the specific camera.
    // The default 3D layer is active and must be restored if changed.
  }

  void onScenePostDraw3D()
  {
    // called once per frame per camera.
    // this is done after all objects are drawn for the specific camera.
    // The default 3D layer is active and must be restored if changed.
    
  }

  void onSceneDraw2D()
  {
    P64::User::deltaTime = P64::User::deltaTime - P64::SceneManager::getCurrent().ticksGlobalDraw;
      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
    for( auto& panel : P64::User::panels) {
      panel->draw(0.01);
    }

    if(P64::User::currentGamemode != nullptr) {
        P64::User::currentGamemode->onDraw2D(0.01);
    }
    
    // called once per frame after all cameras/objects are drawn.
    // The default 2D layer is active and must be restored if changed.
  }
}
