#pragma once

#include "script/userScript.h"
#include "scene/sceneManager.h"
#define DELTATIME_SCALED = sceneManager::getDeltaTime() * sceneManager::getTimeScale();


    struct floatlerpData {
        float cur;
        float final;
        float delta;
        float dur;
    };

    struct vec3lerpData {
        fm_vec3_t cur;
        fm_vec3_t final;
        float delta;
        float dur;
    };

    struct quadrant {
        float x;
        float y;
        int w;
        int h;
    };

namespace Math_Extended {
  extern fm_quat_t LookAt(fm_vec3_t pos1, fm_vec3_t pos2);


}