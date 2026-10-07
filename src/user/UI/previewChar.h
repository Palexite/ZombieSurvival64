#pragma once

#include <cstdint>
#include "scene/components/animModel.h"
#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "utility/splitscreen.h"

namespace Comp {
    class AnimModel;
}

namespace UI {
    class previewChar {

        public:

        Comp::AnimModel* charBody = nullptr;

        P64::Object *linkedObject;
        std::int8_t portId;
        splitscreen::quadrant window;
        P64::ObjectRef CamToDestroy;
        P64::Object *Camera;
        bool camInitialized = false;

        uint16_t CameraId;


        void changeCharacter(int charId);

        void Draw(float deltaTime);

        void Update(float delta);

        previewChar(std::int8_t portId, P64::Object *linkedObject, splitscreen::quadrant window, P64::ObjectRef CamToDestroy);
    };
    
}