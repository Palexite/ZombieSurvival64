#pragma once

#include "libdragon.h"
#include "script/userScript.h"
#include "scene/sceneManager.h"
class Player {
    public:
    int16_t Health = 100;
    bool isDead = false;
    float walkSpeed = 1.0f;
    int portId = 1;
    P64::Object *gameObject = nullptr;

    Player();
    virtual ~Player() = default;
    virtual void Kill(P64::Object obj, int weapon);


};