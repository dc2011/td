#include "ProjectileInputComponent.h"
#include "Projectile.h"
#include "ProjectilePhysicsComponent.h"

ProjectileInputComponent::ProjectileInputComponent() {}

ProjectileInputComponent::~ProjectileInputComponent() { }

void ProjectileInputComponent::update() {
}

void ProjectileInputComponent::setParent(Unit *parent) {
    parent_ = (Projectile*) parent;
}

void ProjectileInputComponent::makeForce() {
}

void ProjectileInputComponent::setPath(QPointF start, QPointF end) {
}
