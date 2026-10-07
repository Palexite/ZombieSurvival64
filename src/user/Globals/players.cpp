#include "players.h"
#include "player/HumanPlayer.h"
#include <map>

namespace players {

    //
    std::vector<playerPref> playerPreferences{};

    // key is the object Id, pointer is the class object that can be either human or zombie
    std::map<uint32_t, std::unique_ptr<Player>> Players{};

    // The total number of ports a player has selected for this game.
    uint8_t portCount = 1;

}