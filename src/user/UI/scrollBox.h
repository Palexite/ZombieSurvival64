#include <vector>
#include "script/userScript.h"
#include "scene/sceneManager.h"


    struct UIItem {
        const char *Thumb;
        const char *Title;
        color_t tint;
    };
namespace UI::ScrollBox
{
extern void DrawScroll(float x, float y, float w, float h,
     color_t bgColor,
    color_t selectColor,
    float iconScale,
    float itemHeight,
    int curPos,
    int drawCount, // number of items to draw at once
    std::vector<UIItem> items);

      extern void DrawItemlayout(float x, float y, float w, float h, UIItem item, float iconScale, color_t selectBgColor, bool isSelected);
}