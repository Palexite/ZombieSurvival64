#include "script/userScript.h"
#include "scene/sceneManager.h"

#include <vector>
#include <string>


#include "../p64/assetTable.h"
#include <libdragon.h>
#include "UI/scrollBox.h"
#include "utility/assets.h"
#include "data/maps_def.h"


namespace P64::Script::CE723306229A98AC
{

              rdpq_textparms_t TEXT_TITLE{
        .width = 256,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true

              };
          rdpq_textparms_t TEXT_DESC{
          .width = 232,
        .align = ALIGN_LEFT,
        .wrap = WRAP_WORD,
        .disable_aa_fix = false

              };

                        rdpq_textparms_t TEXT_STAT{
          .width = 300,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true

              };
  P64_DATA(
    AssetRef<sprite_t> bgSpr;
    uint8_t selectedMap = 0;
    uint8_t selectedCategory = 0;
    std::vector<std::string> categories;

    [[P64::Name("intro script")]]
    ObjectRef introScript;
  );


  void init(Object& obj, Data *data)
  {
        sprite_t *bgTex = (sprite_t*)AssetManager::getByIndex("tex/white.sprite"_asset);
        data->bgSpr.ptr = bgTex;
    // initialization, this is called once when the object spawns
  }

  void destroy(Object& obj, Data *data)
  {
    // clean-up, this is called when the object gets deleted
  }

  void update(Object& obj, Data *data, float deltaTime)
  {

    joypad_buttons_t presButtons = joypad_get_buttons_pressed(JOYPAD_PORT_1);


    if(presButtons.c_down) {
      if(data->selectedMap < data::maps::mapsDefined.size()-1) {
        data->selectedMap++;
      }

    } else if(presButtons.c_up) {
      if(data->selectedMap > 0) {
        data->selectedMap--;
      }
    }
  }




  void draw(Object& obj, Data *data, float deltaTime)
  {
    DrawLayer::use2D();


      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
 
      rdpq_blitparms_s bgParm = {};
    bgParm.scale_x = 480;
    bgParm.scale_y = 280;

     
      rdpq_blitparms_s statsParm = {};
    statsParm.scale_x = 480;
    statsParm.scale_y = 120;

      rdpq_textparms_t titleParms = {};
      titleParms.height = 100;
    rdpq_set_prim_color(RGBA32(0, 64, 128, 128));

    // Create backdrops
    rdpq_sprite_blit(data->bgSpr.ptr, 64, 64, &bgParm);
    rdpq_sprite_blit(data->bgSpr.ptr, 64, 360, &statsParm);


      rdpq_text_printf(&TEXT_TITLE, 2, 180, 48, "MAP SELECT");

    std::vector<UIItem> uiItems = {};
    for (const data::maps::mapDef& map : data::maps::mapsDefined) {
      uiItems.push_back({
        map.icon.c_str(),
        map.name.c_str(),
        RGBA16(31, 31, 31, 1)
      });
    }



      UI::ScrollBox::DrawScroll(64, 64, 256, 280, RGBA32(75, 75, 255, 125), RGBA32(100, 125, 15, 255), .5f, 32, data->selectedMap, 8, uiItems);



      data::maps::mapDef curMap = data::maps::mapsDefined[data->selectedMap];
      
          uint32_t assetIndex = utility::assets::findAssetIndex(curMap.icon.c_str());
          sprite_t *Icon = (sprite_t*)P64::AssetManager::getByIndex(assetIndex);

      rdpq_blitparms_s iconParm = {};
      iconParm.scale_x = 1.5;
      iconParm.scale_y = 1.5;

      rdpq_sprite_blit(Icon, 335, 90, &iconParm);
      rdpq_text_printf(&TEXT_TITLE, 2, 300, 86, curMap.name.c_str());
      rdpq_text_printf(&TEXT_DESC, 1, 324, 200, curMap.desc.c_str());

      const char* difficultyText = "";
      
   switch (curMap.difficulty) {
    case 1:
    difficultyText = "Easy";
    break;
    case 2:
    difficultyText = "Medium";
    break;
    case 3:
    difficultyText = "Hard";
    break;
    case 4:
    difficultyText = "ClusterFuck";
    break;

    default:
        difficultyText = "invalid number dumbass";
        break;
   };

      const char* sizeText = "";
      
   switch (curMap.size) {
    case 1:
    sizeText = "Small";
    break;
    case 2:
    sizeText = "Medium";
    break;
    case 3:
    sizeText = "Large";
    break;
    case 4:
    sizeText = "Huge";
    break;

    default:
      sizeText = "Your mother's 8008s";
      break;
   };
      rdpq_text_print(&TEXT_STAT, 1, -32, 380, "Creator");
      rdpq_text_print(&TEXT_STAT, 1, 72, 380, curMap.originCreator.c_str());

      rdpq_text_print(&TEXT_STAT, 1, -32, 400, "Date");
      rdpq_text_print(&TEXT_STAT, 1, 72, 400, curMap.date.c_str());

      rdpq_text_print(&TEXT_STAT, 1, 200, 380, "Difficulty");
      rdpq_text_print(&TEXT_STAT, 1, 350, 380, difficultyText);

      rdpq_text_print(&TEXT_STAT, 1, 200, 400, "Size");
      rdpq_text_print(&TEXT_STAT, 1, 350, 400, sizeText);
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
  //SceneManager::getCurrent().sendEvent(data->introScript.id, obj.id, 4, 1);
      break;
      case EVENT_TYPE_DISABLE: // object got disabled
      break;

      // you can check for your own custom types here too
    }
  }
}
