#pragma once

// Since Pyrite64 doesn't allow read/writing data of scripts, we need a global space to manage all of it.
// Yes it sucks, but it's the best way atm.

#include "scene/sceneManager.h"
#include "array"
#include <map>


struct ZombieInfo
{
uint8_t PortNumber;
uint8_t zClass;
uint16_t HP;
uint8_t moveSpeed;
bool isDead;

};

struct HumanInfo
{
uint8_t PortNumber;
uint8_t HP;
uint8_t BA;
uint8_t moveSpeed;
bool isDead;
uint16_t Ammo[8];
uint8_t CurrentItem;
uint16_t Items[4];
};



namespace P64::Gameplay {

    std::map<uint16_t, HumanInfo> humansInfo;
    std::map<uint16_t, ZombieInfo> zombiesInfo;

    // Used to determine which port to assign the next created player character.
    int8_t CurrentPortCount = 0;
}
