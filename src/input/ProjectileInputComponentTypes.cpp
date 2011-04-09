#include "ProjectileInputComponentTypes.h"
#include "../engine/Projectile.h"

namespace td {
    
void ArrowProjectileInputComponent::update() {
    if (parent_->getEnemy() != NULL) {
        setPath(&parent_->getPos(), &parent_->getEnemy()->getPos());
    }
    makeForce();
}

} /* end namespace td */
