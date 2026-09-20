#pragma once

#include <libdragon.h>

#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "assets/assetManager.h"
namespace UI {
class Fade {
  float fadeAmount = 0;
  color_t fadeColor = RGBA32(0, 0, 0, 255);
  sprite_t *fadeSpr;
  float x = 0;
  float y = 0;
  float w = 0;
  float h = 0;
  bool destroyOnFadeOut = true;

  rdpq_blitparms_s fadeParm = {};

public:
  Fade(float x, float y, float w, float h, float fadeTime, color_t color, bool fadeIn, bool destroyOnFadeOut);
  ~Fade();
  void fadeDraw(float delta);
  void StartFadeIn();
  void StartFadeOut();

    float curTime = 0;
    float fadeTime = 1;
    bool fadeIn = true;
};
}