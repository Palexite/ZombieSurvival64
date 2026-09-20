#pragma once

#include <libdragon.h>

#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "assets/assetManager.h"
#include <string>

namespace UI {
class CharSelectCorner {
    float x;
    float y;
    float w;
    float h;
    public:
    int characterSelected;
    color_t playerColor;
    int portId;
    CharSelectCorner(float x, float y, float w, float h, int portId);
      ~CharSelectCorner();
      void Draw();
};
}