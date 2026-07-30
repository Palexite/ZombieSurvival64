#pragma once

#include <map>
#include <string>

struct itemDef {
    char16_t name;
    char desc;
    char icon;
    char animPrefix = *"PISTOL1";
    int clipSize = 32;
    int fireRate = 100;
    int spread = 4;
    int shotsPerFire = 4;
    float recoil = 1;

    char WorldModel;
    char FireParticle = *"PISTOL1";
    char FireSound = *"PISTOL1";
    char reloadSound;





};

namespace Items {



std::map<std::string, itemDef> itemDefs;


}