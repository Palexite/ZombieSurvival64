#pragma once

#include <libdragon.h>

#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "scene/camera.h"
#include "assets/assetManager.h"
#include "colorPicker.h"

#include "Panel.h"

#include "utility/math.h"
#include "utility/controllerpak.h"

#include <string>

namespace UI {
class CharSelectCorner : public UI::Panel{

    float colorHuePick = 0;
    float colorLightPick = 0;
    P64::Camera* camera = nullptr;

    public:
    int characterSelected = 0;
    P64::Object* PreviewCharacter = nullptr;
    color_t playerColor = RGBA32(255, 255, 255, 255);

    int portId = 1;

    UI::ColorPicker *colorPicker = nullptr;
    PlayerData* pData = nullptr;

    CharSelectCorner(int portId, P64::Object* previewCharacter);
      ~CharSelectCorner();
      void draw(float deltaTime) override;
      void update(float deltaTime) override;
      void ChangeCharacter(int charId);

      private:
      uint16_t smallFontID;
};
}