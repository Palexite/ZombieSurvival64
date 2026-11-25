#pragma once

#include "scene/sceneManager.h"
#include "array"
#include <map>
#include <memory>
#include "Gamemodes/gamemode.h"

namespace Game {
    
    // Used to determine which port to assign the next created player character.
    extern int8_t CurrentPortCount;
    extern std::unique_ptr<Gamemode> currentGamemode;

}
