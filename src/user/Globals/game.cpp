#include "game.h"
#include "Gamemodes/zombiesurvival.h"
#include "scene/sceneManager.h"
#include "Globals/global.h"
#include "Globals/players.h"

namespace Game {

    // This value must correspond to the joypad_port_t enum during the entirety of gameplay.
    // This value is incremented by 1 for each user, so -1 is needed.
    int8_t CurrentPortCount = -1;
    std::unique_ptr<Gamemode> currentGamemode = std::make_unique<GM_ZombieSurvival>(P64::User::mapSelected, players::portCount);
}