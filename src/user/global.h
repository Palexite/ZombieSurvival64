#pragma once

#include <map>

namespace P64::User {
extern uint8_t portCount;
extern uint8_t flags;
// 1 = Human, 0 = Zombie
extern uint8_t portTeam;
extern uint8_t mapSelected;


struct mapDef {
uint16_t Scene;
uint8_t Difficulty;
const char *Name;
const char *Desc;
const char *Creator;
const char *OriginCreator;
const char *Thumb;
bool IsObj;
};

extern mapDef MapsDefined[16];



extern std::map<char, uint16_t> HumanAnimsDef;

uint16_t GetHumanAnimationByName(char animName);




/*
mapDef MapsDefined[1] = {
[1] = {
   .Scene = 1, 
   .Difficulty = 1,
     .Name = "Abandoned Mall", 
    .Desc = "One of the first Zombie Survival Maps ever built, even preceding the gamemode",
    .Creator = "Anonymous",
    .OriginCreator = "Anonymous",
    .Thumb = "Anonymous",
    .IsObj = false
}
*/
};