#pragma once

#include <vector>
#include "previewChar.h"
#include "script/userScript.h"
#include "scene/sceneManager.h"
#include <cstdint>

namespace UI {
    class CharSelect {

    public:
    P64::Object& linkedObject;

    P64::ObjectRef placeholdCamera;
     // Preview characters we need to add at the next frame (because they don't exist yet)
    std::vector<uint16_t> deferredChars = {};

    std::vector<UI::previewChar> prevChars = {};

    int currentPortCount = 1;

    CharSelect(P64::Object& linkedObject, P64::ObjectRef placeholdCamera);

    void update(P64::Object& obj, float deltaTime);

    void draw(float deltaTime);
    };
}