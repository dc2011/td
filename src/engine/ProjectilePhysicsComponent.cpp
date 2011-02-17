#include "ProjectilePhysicsComponent.h"
#include "Projectile.h"

ProjectilePhysicsComponent::ProjectilePhysicsComponent() : maxVelocity_(10) {}
ProjectilePhysicsComponent::~ProjectilePhysicsComponent() {}

void ProjectilePhysicsComponent::update(Unit* projectile)
{
    //this->applyVelocity((Projectile*)projectile);
}

void ProjectilePhysicsComponent::applyVelocity(Projectile* projectile) {

}
