#pragma once

#include "script/userScript.h"
#include "scene/sceneManager.h"
#include <string>
#include "utility/math.h"
#include "style.h"
#include <functional>

namespace UI {
    class GradientButton {
        public:

        std::string text;

        quadrant quad;

        buttonScheme scheme;
        
        std::function<void()> onEnter;

        bool isHovered;

        GradientButton(std::string text, quadrant quad, buttonScheme scheme, std::function<void()> onEnter);

        ~GradientButton();

        void draw(float deltaTime);

        void Enter();

        void update(float deltaTime);

        private:
        uint16_t fontId = 1;
    };
}