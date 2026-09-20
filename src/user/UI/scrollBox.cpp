#include <string_view>
#include "../../p64/assetTable.h"
#include <libdragon.h>
#include <list>
#include "scrollBox.h"
#include "utility/assets.h"

namespace UI::ScrollBox
{
          rdpq_textparms_t TEXT_MAPNAME{
        .width = 300,
        .align = ALIGN_CENTER,
        .disable_aa_fix = true
    };


  //Draws a basic scroll box. This one is used for map selection.
  void DrawScroll(float x, float y, float w, float h,
     color_t bgColor,
    color_t selectColor,
    float iconScale,
    float itemHeight,
    int curPos,
    int drawCount, // number of items to draw at once
    std::vector<UIItem> items)
    
    {
        sprite_t *bg = (sprite_t*)P64::AssetManager::getByIndex("tex/white.sprite"_asset);

              rdpq_blitparms_s bgParm = {};
            bgParm.scale_x = w;
            bgParm.scale_y = h;


            rdpq_set_prim_color(bgColor);
            rdpq_sprite_blit(bg, x, y, &bgParm);

    if(drawCount >= (int)items.size()) {
                for(int i = 0; i < (int)items.size(); i++) {
                  
                  DrawItemlayout(x, y + (i * itemHeight) + 16, w, itemHeight, items[i], iconScale, selectColor, curPos == i);



                }
    } else {
      for(int i = curPos - (drawCount / 2); i < curPos + (drawCount / 2); i++) {
          if(i >= 0) {
          DrawItemlayout(x, y + ((i - curPos + (drawCount/2)) * itemHeight), w, itemHeight, items[i], iconScale, selectColor, curPos == i);
          }
        }
    
    }
    }    

  void DrawItemlayout(float x, float y, float w, float h, UIItem item, float iconScale, color_t selectBgColor, bool isSelected) {



      uint32_t assetIndex = utility::assets::findAssetIndex(item.Thumb);
      if (assetIndex == UINT32_MAX) {
        return;
      }
      
      if(isSelected) {
              sprite_t *bg = (sprite_t*)P64::AssetManager::getByIndex("tex/white.sprite"_asset);

            rdpq_blitparms_s bgParm = {};
            bgParm.scale_x = w;
            bgParm.scale_y = h;
        rdpq_set_prim_color(selectBgColor);
        rdpq_sprite_blit(bg, x, y - (32 * iconScale), &bgParm);
      }

      sprite_t *Icon = (sprite_t*)P64::AssetManager::getByIndex(assetIndex);

      rdpq_blitparms_s iconParm = {};
      iconParm.scale_x = iconScale;
      iconParm.scale_y = iconScale;

      rdpq_set_prim_color(item.tint);
      if (Icon) {
        rdpq_sprite_blit(Icon, x, y - (32 * iconScale), &iconParm);
      }

        rdpq_text_print(&TEXT_MAPNAME, 1, x, y, item.Title);
  }

}
