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
}

void Player::update() {
    physics_->update(this);
    graphics_->update(this);
}

