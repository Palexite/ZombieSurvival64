#pragma once

#include <map>
#include <string>

struct itemDef {
    const char* name;
    const char* desc;
    const char* icon;
    const char* animPrefix = "PISTOL1";
    int clipSize = 32;
    int fireRate = 100;
    int spread = 4;
    int shotsPerFire = 4;
    float recoil = 1;

    const char* WorldModel;
    const char* FireParticle = "PISTOL1";
    const char* FireSound = "PISTOL1";
    const char* reloadSound;





};

namespace Items {



std::map<std::string, itemDef> itemDefs;


}