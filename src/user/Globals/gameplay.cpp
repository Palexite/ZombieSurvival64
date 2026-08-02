#include "gameplay.h"

namespace P64::Gameplay {
    std::map<uint16_t, HumanInfo> humansInfo = {};
    std::map<uint16_t, ZombieInfo> zombiesInfo = {};

    // This value must correspond to the joypad_port_t enum during the entirety of gameplay.
    // This value is incremented by 1 for each user, so -1 is needed.
    int8_t CurrentPortCount = -1;
}