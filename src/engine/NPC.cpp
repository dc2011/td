#include "NPC.h"

NPC::NPC(PhysicsComponent* physics) {
    physics_ = physics;
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
}
