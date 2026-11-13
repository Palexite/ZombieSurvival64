#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "data/maps_def.h"
#include "data/chars_def.h"
#include "UI/Panel.h"

namespace P64::User {
extern uint8_t flags;
// 1 = Human, 0 = Zombie
extern uint8_t portTeam;
extern uint8_t mapSelected;
extern std::vector<std::unique_ptr<UI::Panel>> panels;

extern data::maps::mapDef MapsDefined[16];
}