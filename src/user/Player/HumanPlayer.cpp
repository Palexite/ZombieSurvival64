#include "HumanPlayer.h"
#include "scene/sceneManager.h"
#include "data/chars_def.h"

#include "utility/assets.h"

PlayerHuman::~PlayerHuman() = default;

PlayerHuman::PlayerHuman(uint8_t charId, uint8_t portId) : CharId(charId), portId(portId) {
    std::string charAsset = data::characters::charsDefined[charId].gameAsset;

    this->gameObjectId = P64::SceneManager::getCurrent().addObject(utility::assets::findAssetIndex(charAsset.c_str()));
}

void PlayerHuman::update(float deltaTime) {
    Player::update(deltaTime);
}

void PlayerHuman::draw(float deltaTime) {
}

void PlayerHuman::updateInput(float deltaTime) {
    
}

