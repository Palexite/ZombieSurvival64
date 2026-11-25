#pragma once

#include <libdragon.h>

#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "scene/camera.h"
#include "assets/assetManager.h"

#include "colorPicker.h"
#include "SwitchPlate.h"

#include "Panel.h"

#include "utility/math.h"
#include "utility/controllerpak.h"

#include "data/chars_def.h"

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
    UI::SwitchPlate* charSelectPlate = nullptr;


    PlayerData* pData = nullptr;

    CharSelectCorner(int portId, P64::Object* previewCharacter);
      ~CharSelectCorner();
      void draw(float deltaTime) override;
      void update(float deltaTime) override;
      void ChangeCharacter(int charId);

      private:

        // Camera interpolation variables

        float cameraFOV_Cur;
        float cameraFOV_Delta;
        float cameraFOV_Final;

        fm_vec3_t cameraPos_Cur;
        float cameraPos_Delta;
        fm_vec3_t cameraPos_Final;


      uint16_t smallFontID;
};
}