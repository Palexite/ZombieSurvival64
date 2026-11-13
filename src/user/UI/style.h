#pragma once

#include "script/userScript.h"
#include "scene/sceneManager.h"

#include "libdragon.h"

/// @brief In-house styling for UI buttons.
/// @param baseColor the color of the button in it's inactive state
/// @param hoverColor the color of the button in it's hovered state
/// @param font the font name of the button
struct buttonScheme {
    color_t baseColor;
    color_t hoverColor;
    std::string font;
};

namespace UI::Gradient {
    extern void DrawMiddleGradient(int x, int y, int fill, int width, int height, color_t color);
}