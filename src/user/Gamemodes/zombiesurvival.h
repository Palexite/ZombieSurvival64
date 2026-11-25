#include "gamemode.h"

class GM_ZombieSurvival : public Gamemode {

public:
    GM_ZombieSurvival(int16_t mapId, int16_t portCount);
    virtual ~GM_ZombieSurvival();

    virtual void onGameUpdate(float deltaTime);

    virtual void onGameStart();

    void RoundUpdate();

    void escapeSequence();

    void lastHumanSequence();



    float baseWaveDuration = 60;

    uint16_t round = 0;
    float roundTime = 120;
    bool roundActive = false;
    bool humansEscaping = false;
    bool lastHuman = false;
    bool zombiesCanSpawn = false;
};