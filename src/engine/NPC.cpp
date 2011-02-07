#include "NPC.h"

using namespace std;

NPC::NPC(PhysicsComponent* physics) {
    physics_ = physics;
}

size_t NPC::GetHealth() {
    return health_;
}

void NPC::SetHealth(size_t health){
    health_ = health;
}

size_t NPC::GetDamage() {
    return damage_;
}

void NPC::SetDamage(size_t damage) {
    damage_ = damage;
}

void NPC::Update() {
    physics_->Update(this);
}
