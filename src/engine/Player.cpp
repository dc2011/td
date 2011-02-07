#include "Player.h"

Player::Player(InputComponent* input, PhysicsComponent* physics) {
    QVector2D force(0, 0);
    this->setForce(force);
    input_ = input;
    input_->setParent(this);
    
    physics_ = physics;
}

void Player::update() {
    physics_->update(this);
}
