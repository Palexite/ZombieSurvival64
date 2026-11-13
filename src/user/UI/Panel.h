#pragma once

#include "utility/math.h"

namespace UI {
    class Panel {
    public:

        quadrant bounds = {0, 0, 0, 0};
        Panel() = default;
        virtual ~Panel() = default;

        virtual void draw(float deltaTime) = 0;
        virtual void update(float deltaTime) = 0;

    };
}