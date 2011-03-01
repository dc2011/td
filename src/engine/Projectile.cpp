#include "Projectile.h"

Projectile::Projectile() : Unit(),
        start_(new QPointF(0,0)), end_(new QPointF(0,0))
{
    path_ = QLineF(end_->x(), end_->y(), start_->x(), start_->y());
}

Projectile::Projectile(PhysicsComponent* physics, GraphicsComponent* graphics,
                       QPointF* start, QPointF* end) {
    physics_ = physics;
    graphics_ = graphics;
    input_ = NULL;
    this->setPos(start->x(),start->y());
    scale_ = 0.25;
    start_ = start;
    end_ = end;
    path_ = QLineF(end->x(), end->y(), start->x(), start->y());
}

void Projectile::update() {
    physics_->update(this);
    graphics_->update(this);
}

