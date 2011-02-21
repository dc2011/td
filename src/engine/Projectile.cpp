#include "Projectile.h"

Projectile::Projectile(PhysicsComponent* physics, 
        GraphicsComponent* graphics, QPointF* start, QPointF* end) {
    physics_ = physics;
    graphics_ = graphics;
    start_ = start;
    end_ = end;
}

void Projectile::update() {
    physics_->update(this);
    graphics_->update(this);
}

