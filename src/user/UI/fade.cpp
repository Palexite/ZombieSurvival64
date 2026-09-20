#include <string_view>
#include <algorithm>
#include "../../p64/assetTable.h"
#include <libdragon.h>
#include "math.h"
#include "fade.h"

namespace UI {
Fade::Fade(float x, float y, float w, float h, float fadeTime, color_t color, bool fadeIn, bool destroyOnFadeOut) {
    fadeSpr = (sprite_t*)P64::AssetManager::getByIndex("tex/white.sprite"_asset);
    fadeColor = color;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->fadeTime = fadeTime;
    this->fadeIn = fadeIn;
    this->destroyOnFadeOut = destroyOnFadeOut;


    fadeParm.scale_x = w;
    fadeParm.scale_y = h;
}

  Fade::~Fade() = default;

void Fade::StartFadeIn() {
  this->curTime = 0;
  this->fadeIn = true;
}

void Fade::StartFadeOut() {
  this->curTime = 0;
  this->fadeIn = false;
}

void Fade::fadeDraw(float delta) {
      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
    curTime += delta;
    fadeAmount = std::clamp(curTime / fadeTime, 0.0f, 1.0f);
    if(fadeIn) {
      fadeColor = RGBA32(fadeColor.r, fadeColor.g, fadeColor.b, (uint8_t)(fadeAmount * 255));
    } else {
      fadeColor = RGBA32(fadeColor.r, fadeColor.g, fadeColor.b, (uint8_t)((1 - fadeAmount) * 255));

      if(curTime >= fadeTime && this->destroyOnFadeOut) {
        
      }
    }
    rdpq_set_prim_color(fadeColor);
    rdpq_sprite_blit(fadeSpr, x, y, &this->fadeParm);
}
}
