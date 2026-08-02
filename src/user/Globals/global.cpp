#include "script/globalScript.h"
#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "global.h"

namespace P64::User {

  uint8_t portCount = 1;
  uint8_t flags = 0;
  // 1 = Human, 0 = Zombie
  uint8_t portTeam = 1;
  uint8_t mapSelected = 0;

  mapDef MapsDefined[16] = {};
  std::map<char, uint16_t> HumanAnimsDef = {};




  uint16_t GetHumanAnimationByName(char animName) {
      if(User::HumanAnimsDef.at(animName) != 0) {
      return User::HumanAnimsDef.at(animName);
    } else return 0;
  }
}


namespace P64::GlobalScript::C6EFF0964420055D
{
  // The following functions are called by the engine at different points in the games lifecycle.
  // If you don't need a specific function you can remove it.
  // This script is hooked up automatically and doesn't need any setup in the editor.

void SetupMaps() {
    User::MapsDefined[0].Name = "Abandoned Mall";
    User::MapsDefined[0].OriginCreator = "";
    User::MapsDefined[0].Difficulty = 1;
    User::MapsDefined[0].Desc = "";
    User::MapsDefined[0].Scene = 1;
    User::MapsDefined[0].Thumb = "";
}


void SetupAnimations() {
User::HumanAnimsDef[*"INTRO_MELEE2_1"] = 1;


}

  void onGameInit()
  {
        SetupMaps();

        rdpq_font_t *font = rdpq_font_load("rom:/fonts/RemingtonNoiseless_Med_1.font64");

        rdpq_fontstyle_t normal = {};
        normal.color = RGBA16(31, 31, 31, 1);
        rdpq_fontstyle_t outlineStyle = {};

        outlineStyle.color = RGBA16(0, 0, 0, 1);
  rdpq_font_style(font, 0, &normal);
  rdpq_font_style(font, 1, &outlineStyle);
  rdpq_text_register_font(1, font);

    // called once when the game starts, all other systems (e.g. asset manager) are already inititalized
  }

  void onScenePreLoad()
  {
    // right before a new scene is loaded
  }

  void onScenePostLoad()
  {
    // right after a new scene was loaded, but before any update has happened yet
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
    // called once per frame after all cameras/objects are drawn.
    // The default 2D layer is active and must be restored if changed.
  }
}
