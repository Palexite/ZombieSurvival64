#pragma once

#include "math.h"
#define scrW 640
#define scrH 480

namespace splitscreen {


    quadrant calculateDimensions(int step, int divisions);

    extern quadrant fitQuadToBounds(quadrant relativeQuad, quadrant bounds);

    extern uint8_t curScreenDivisions;
}