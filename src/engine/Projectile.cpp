#include "Projectile.h"

Projectile::Projectile(PhysicsComponent* physics, GraphicsComponent* graphics,
                       QPointF* sender, QPointF* receiver) {
    physics_ = physics;
    graphics_ = graphics;
    sender_ = sender;
    receiver_ = receiver;
}

void Projectile::update() {
    physics_->update(this);
    graphics_->update(this);
}

