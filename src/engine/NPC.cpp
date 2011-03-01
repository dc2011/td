#include "NPC.h"

NPC::NPC(PhysicsComponent* physics, InputComponent* input,
         GraphicsComponent* graphics) {
    physics_ = physics;
    input_ = input;
    graphics_ = graphics;
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
