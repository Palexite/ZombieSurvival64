#pragma once

/// @brief Rerepesents rules of the game, as well as other behaviors.
#include "utility/math.h"

class Gamemode {

public:
    Gamemode(int16_t mapId, int16_t portCount);
    virtual ~Gamemode();

    virtual void onGameStart();
    
    virtual void onDraw2D(float deltaTime);

    virtual void onGameUpdate(float deltaTime);

    virtual void playerRespawnRequest(int16_t playerId);
};