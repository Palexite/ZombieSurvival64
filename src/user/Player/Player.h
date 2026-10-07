#pragma once

#include "libdragon.h"
#include "script/userScript.h"
#include "scene/sceneManager.h"
class Player {
    public:
    int16_t Health;
    bool isDead;
    float walkSpeed;
    int portId;
    P64::Object *gameObject;

    Player();
    virtual ~Player() = default;
    void Kill(P64::Object obj, int weapon);


};