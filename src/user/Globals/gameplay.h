#pragma once

// Since Pyrite64 doesn't allow read/writing data of scripts, we need a global space to manage all of it.
// Yes it sucks, but it's the best way atm.

#include "scene/sceneManager.h"
#include "array"
#include <map>

namespace Gameplay {
    
    // Used to determine which port to assign the next created player character.
    extern int8_t CurrentPortCount;


        extern void GameStart();
}
