#pragma once

#include "Player.h"
#include "scene/components/animModel.h"
#include "scene/components/camera.h"

class PlayerHuman : public Player {
    public:
    PlayerHuman(uint8_t charId, uint8_t portId);
    ~PlayerHuman();
    uint8_t CharId = 0;
    uint8_t portId = 0;
    uint16_t BloodArmor = 0;
    P64::Comp::AnimModel *mainModel = nullptr;
    P64::Comp::Camera *camera = nullptr;

    void draw(float deltaTime) override;
    //void tickView(float deltaTime) override;
    void updateInput(float deltaTime) override;
    void update(float deltaTime) override;
};