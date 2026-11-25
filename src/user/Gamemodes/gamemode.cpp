#include "gamemode.h"

Gamemode::~Gamemode() = default;

Gamemode::Gamemode(int16_t mapId, int16_t portCount) {}

void Gamemode::onGameUpdate(float deltaTime) {}

void Gamemode::playerRespawnRequest(int16_t playerId) {}

void Gamemode::onDraw2D(float deltaTime) {}

void Gamemode::onGameStart() {}