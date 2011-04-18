#include "ProjectilePhysicsComponentTypes.h"
#include "../util/defines.h"
#include "../engine/Projectile.h"

namespace td {

ArrowProjectilePhysicsComponent::ArrowProjectilePhysicsComponent()
    : ProjectilePhysicsComponent(ARROW_VELOCITY) {}

void ArrowProjectilePhysicsComponent::setScale(Projectile *projectile) {
    if (duration_ < 0) {
        duration_ = projectile->getPath().length() / maxVelocity_;
        increment_ = 0;
    }
    if (increment_++ < (duration_ / 2)) {
        projectile->setScale(projectile->getScale() + 0.05);
    } else if (increment_ < duration_) {
        projectile->setScale(projectile->getScale() - 0.05);
    }
}

CannonProjectilePhysicsComponent::CannonProjectilePhysicsComponent()
    : ProjectilePhysicsComponent(CANNON_VELOCITY) {}

void CannonProjectilePhysicsComponent::setScale(Projectile *projectile) {
    if (duration_ < 0) {
        duration_ = projectile->getPath().length() / maxVelocity_;
        increment_ = 0;
    }
    if (increment_++ < (duration_ / 2)) {
        projectile->setScale(projectile->getScale() + 0.075);
    } else if (increment_ < duration_) {
        projectile->setScale(projectile->getScale() - 0.075);
    }
}

FireProjectilePhysicsComponent::FireProjectilePhysicsComponent()
    : ProjectilePhysicsComponent(FIRE_VELOCITY) { duration_ = 0;}

void FireProjectilePhysicsComponent::setScale(Projectile* projectile) {
    if(++duration_ > FIRE_SCALE_TIME && duration_ < FIRE_DURATION) {
        //pause image from growing
        projectile->setPos(projectile->getEndPoint()->x(), 
                projectile->getEndPoint()->y());
    } else if (duration_ > FIRE_DURATION) {
        //delete projectile;
    }
}

TarProjectilePhysicsComponent::TarProjectilePhysicsComponent()
    : ProjectilePhysicsComponent(TAR_VELOCITY) {}

void TarProjectilePhysicsComponent::setScale(Projectile *projectile) {
    if (duration_ < 0) {
        duration_ = projectile->getPath().length() / maxVelocity_;
        increment_ = 0;
    }
    if (increment_++ < (duration_ / 2)) {
        projectile->setScale(projectile->getScale() + 0.075);
    } else if (increment_ < duration_) {
        projectile->setScale(projectile->getScale() - 0.075);
    }
}

FlakProjectilePhysicsComponent::FlakProjectilePhysicsComponent()
    : ProjectilePhysicsComponent(FLAK_VELOCITY) {}

void FlakProjectilePhysicsComponent::setScale(Projectile *projectile) {
    if (duration_ < 0) {
        duration_ = projectile->getPath().length() / maxVelocity_;
        increment_ = 0;
    }
    if (increment_++ < (duration_ / 1.5)) {
        projectile->setScale(projectile->getScale() + 0.05);
    } else if (increment_ < duration_) {
        projectile->setScale(projectile->getScale() - 0.05);
    }
}

} /* end namespace td */

