#include "zombiesurvival.h"
#include "Globals/players.h"
#include "Player/HumanPlayer.h"
#include <vector>
#include <memory>
#include <map>
#include <utility>

GM_ZombieSurvival::~GM_ZombieSurvival() = default;

GM_ZombieSurvival::GM_ZombieSurvival(int16_t mapId, int16_t portCount) : Gamemode(mapId, portCount) {}

void GM_ZombieSurvival::RoundUpdate() {
        if(!this->roundActive) {
            this->roundTime = this->baseWaveDuration + (this->round * 20);
            this->roundActive = true;
            this->zombiesCanSpawn = true;
            this->round++;
        } else {

            if(this->round > 6) {
                this->escapeSequence();
                return;
            }

            this->roundActive = false;
            this->zombiesCanSpawn = false;
            this->roundTime = this->baseWaveDuration + (this->round * 20) * 0.6f;
        }
}

void GM_ZombieSurvival::onGameStart() {
    for(uint32_t i = 0; i < players::portCount; i++) {

        std::unique_ptr<PlayerHuman> newPlayer = std::make_unique<PlayerHuman>(1, i);
        players::Players.emplace(i, std::move(newPlayer));
    }
}

void GM_ZombieSurvival::onGameUpdate(float deltaTime) {

    roundTime -= deltaTime;

    if(roundTime <= 0) {
        RoundUpdate();
    }

}

void GM_ZombieSurvival::escapeSequence() {
    this->humansEscaping = true;
    this->roundTime = 30;
}

void GM_ZombieSurvival::lastHumanSequence() {
    this->lastHuman = true;
}

