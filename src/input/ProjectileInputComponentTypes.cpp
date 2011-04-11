#include "ProjectileInputComponentTypes.h"
#include "../engine/Projectile.h"
#include <QPointF>

namespace td {
    
void ArrowProjectileInputComponent::update() {
    if (parent_->getEnemy() != NULL) {
        QPointF* start = new QPointF(parent_->getPos().x(),
                                     parent_->getPos().y());
        QPointF* end = new QPointF(parent_->getEnemy()->getPos().x(),
                                   parent_->getEnemy()->getPos().y());
        setPath(start, end);
    }
    makeForce();
}

} /* end namespace td */
