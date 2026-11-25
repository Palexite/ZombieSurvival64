#pragma once

#include "libdragon.h"
#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "scene/components/charBody.h"
#include "scene/components/camera.h"
class Player {
    public:
    int16_t Health = 100;

    bool isDead = false;
    bool isFrozen = false;
    bool canMove = false;


    float walkSpeed = 1.0f;
    float acceleration = 10.0f;
    fm_vec3_t inputVelocity = fm_vec3_t({0, 0, 0});
    fm_vec3_t baseVelocity = fm_vec3_t({0, 0, 0});
    fm_vec3_t velocity = fm_vec3_t({0, 0, 0});

    fm_vec3_t viewOffset = fm_vec3_t({0, 0, 0});
    float life = 0.0f;
    float vBobScale = 0.05f;
    float vBobSpeed = 0.05f;

    int portId = 1;



    P64::Object *gameObject = nullptr;
    P64::Comp::CharBody *charBody = nullptr;
    P64::Comp::Camera *camera = nullptr;
    uint16_t gameObjectId = 0;

    Player();
    virtual ~Player() = default;
    virtual void kill(P64::Object obj, int weapon);

    virtual void draw(float deltaTime);
    virtual void tickView(float deltaTime);

    virtual void updateInput(float deltaTime);
    virtual void updateMovement(float deltaTime);
    virtual void updateAnimation(float deltaTime);
    virtual void update(float deltaTime);

};