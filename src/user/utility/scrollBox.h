#include "script/userScript.h"
#include "scene/sceneManager.h"


    struct UIItem {
        char *Thumb;
        char *Title;
        color_t tint;
    };
namespace UI::ScrollBox
{


extern void DrawScroll(float x, float y, float w, float h,
     color_t bgColor,
    color_t selectColor,
    float itemHeight,
    int curPos,
    int drawCount, // number of items to draw at once
    UIItem items[]);


}
