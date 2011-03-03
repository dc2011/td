#include "NPC.h"

NPC::NPC(InputComponent* input,PhysicsComponent* physics, GraphicsComponent* graphics) {
    physics_ = physics;
    graphics_ = graphics;
    QVector2D force(0, 0);
    this->setForce(force);
    input_ = input;
    input_->setParent(this);
    pos_.setX(50);
    pos_.setY(50);
}

size_t NPC::getHealth() {
    return health_;
}

void NPC::setHealth(size_t health){
    health_ = health;
}

size_t NPC::getDamage() {
    return damage_;
}

void NPC::setDamage(size_t damage) {
    damage_ = damage;
}

void NPC::update() {
    physics_->update(this);
    graphics_->update(this);
}
