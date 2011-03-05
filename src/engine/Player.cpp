#include "Player.h"

Player::Player(InputComponent* input, PhysicsComponent* physics,
               GraphicsComponent* graphics, CollisionComponent* collision) {
    QVector2D force(0, 0);
    this->setForce(force);
    input_ = input;
    input_->setParent(this);
    
    physics_ = physics;
    graphics_ = new PlayerGraphicsComponent();

    collision_ = collision;
    collision_->setParent(this);

    this->setPos(100, 100);
}

void Player::update() {
    physics_->update(this);
    if (this->getDirtyStatus()) {
        collision_->update(this->getPos());
    }
    graphics_->update(this);
}

