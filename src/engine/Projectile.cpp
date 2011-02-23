#include "Projectile.h"

Projectile::Projectile(PhysicsComponent* physics, GraphicsComponent* graphics,
                       QPointF* start, QPointF* end) {
    physics_ = physics;
    graphics_ = graphics;
    input_ = NULL;
    this->setPos(start->x(),start->y());
    start_ = start;
    end_ = end;
    path_ = QLineF(end->x(), end->y(), start->x(), start->y());
}

void Projectile::update() {
    physics_->update(this);
    graphics_->update(this);
}

