#include "script/userScript.h"
#include "scene/sceneManager.h"

#include <libdragon.h>
#include <list>
#include "scrollBox.h"
#include "../p64/assetTable.h"

namespace UI::ScrollBox
{
inline void DrawScroll(float x, float y, float w, float h,
     color_t bgColor,
    color_t selectColor,
    float itemHeight,
    int curPos,
    int drawCount, // number of items to draw at once
    int itemCount,
    UIItem items[4])
    
    {


    if(drawCount >= itemCount) {

    } else {
      for(int i = curPos - (drawCount / 2); i < drawCount; i++) {
        char assetName[128];
        //sprite_t *Icon = (sprite_t*)AssetManager::getByIndex(assetName);
        
      }
    


    }
  }

}
