#include "Player.h"
#include <algorithm>

Player::Player() = default;

void Player::kill(P64::Object obj, int Weapon) {

}

void Player::update(float deltaTime) {
    if(this->gameObject == nullptr) {
        this->gameObject = P64::SceneManager::getCurrent().getObjectById(gameObjectId);

        this->charBody = gameObject->getComponent<P64::Comp::CharBody>(0);
        this->camera = gameObject->getComponent<P64::Comp::Camera>(0);
        return;
    }
    this->updateInput(deltaTime);
    this->updateMovement(deltaTime);
    this->updateAnimation(deltaTime);
}

void Player::tickView(float deltaTime) {
    this->life += deltaTime;

    this->vBobScale = std::sin(this->life * this->vBobSpeed) * this->vBobScale;
    fm_vec3_t newPos = this->gameObject->pos + this->viewOffset;

    if(this->camera != nullptr) {
        this->camera->camera.setPosRot(newPos, this->gameObject->rot);
    }

}

void Player::updateMovement(float deltaTime) {
    if(!this->isFrozen) {
    this->baseVelocity = this->baseVelocity * inputVelocity * this->acceleration * deltaTime;
    this->baseVelocity.x = std::clamp(this->baseVelocity.x, -this->walkSpeed, this->walkSpeed);
    this->baseVelocity.z = std::clamp(this->baseVelocity.z, -this->walkSpeed, this->walkSpeed);
    this->velocity = this->baseVelocity;

    if(this->charBody != nullptr) {
        this->charBody->getBody().inputVelocity = this->velocity;
        this->charBody->getBody().moveAndSlide(deltaTime);
    }
    }

}

void Player::updateInput(float deltaTime) {
    joypad_buttons_t buttons = joypad_get_buttons_held(static_cast<joypad_port_t>(this->portId));
    this->inputVelocity = fm_vec3_t{0, 0, 0};
    if(canMove) {

        if(buttons.c_up) {
            this->inputVelocity.z = 1;
        } else if(buttons.c_down) {
            this->inputVelocity.z = -1;
        } else if(buttons.c_left) {
            this->inputVelocity.x = -1;
        } else if(buttons.c_right) {
            this->inputVelocity.x = 1;
        }
    }
}
void Player::updateAnimation(float deltaTime) {

}

void Player::draw(float deltaTime) {

}