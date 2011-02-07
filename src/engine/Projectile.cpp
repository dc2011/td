#include "Projectile.h".h"

using namespace std;

Projectile::Projectile(PhysicsComponent* physics, Unit* sender, Unit* receiver) {
    physics_ = physics;
    sender_ = sender;
    receiver_ = receiver;
}

QVector2D& Projectile::GetVelocity() {
    return velocity_;
}

void Projectile::SetVelocity(QVector2D& velocity) {
    velocity_ = velocity;
}

size_t Projectile::GetDamage(){
    return damage_;
}

void Projectile::SetDamage(size_t damage){
    damage_ = damage;
}

size_t Projectile::GetDuration(){
    return duration_;
}

void Projectile::SetDuration(size_t duration){
    duration_ = duration;
}

void Projectile::Update() {
    physics_->Update(this);
}

