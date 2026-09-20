#pragma once

#include <string>
#include <map>
#include "data/maps_def.h"

namespace P64::User {
extern uint8_t portCount;
extern uint8_t flags;
// 1 = Human, 0 = Zombie
extern uint8_t portTeam;
extern uint8_t mapSelected;


extern data::maps::mapDef MapsDefined[16];



extern std::map<std::string, uint16_t> HumanAnimsDef;

uint16_t GetHumanAnimationByName(const char* animName);

}