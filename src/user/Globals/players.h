
#include "libdragon.h"
#include "player/Player.h"
#include <memory>
#include <vector>
#include <map>

namespace players {

    struct playerPref {
        int Character;
        color_t playerColor;
    };

    extern std::vector<playerPref> playerPreferences;
    extern std::map<uint32_t, std::unique_ptr<Player>> Players;
    extern uint8_t portCount;
}