#include "Projectile.h"

Projectile::Projectile(PhysicsComponent* physics, Unit* sender, Unit* receiver) {
    physics_ = physics;
    sender_ = sender;
    receiver_ = receiver;
}

QVector2D& Projectile::getVelocity() {
    return velocity_;
}

void Projectile::setVelocity(QVector2D& velocity) {
    velocity_ = velocity;
}

size_t Projectile::getDamage(){
    return damage_;
}

void Projectile::setDamage(size_t damage){
    damage_ = damage;
}

size_t Projectile::getDuration(){
    return duration_;
}

void Projectile::setDuration(size_t duration){
    duration_ = duration;
}

void Projectile::update() {
    physics_->update(this);
}

