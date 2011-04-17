#include "ProjectileGraphicsComponent.h"
#include "../engine/Projectile.h"

namespace td {

ProjectileGraphicsComponent::ProjectileGraphicsComponent()
        : GraphicsComponent() {
    animate_ = true;
}

ProjectileGraphicsComponent::~ProjectileGraphicsComponent() {}

void ProjectileGraphicsComponent::update(GameObject* obj) {
    Projectile* projectile = (Projectile*)obj;

    if (!projectile->isDirty()) {
        return;
    }
    projectile->resetDirty();

    pos_ = projectile->getPos();
    scale_ = projectile->getScale();
    degrees_ = projectile->getOrientation();
    DrawParams* dp = new DrawParams();
    dp->pos     = projectile->getPos();
    dp->scale   = projectile->getScale();
    dp->degrees = projectile->getOrientation();
    dp->animate = animate_;
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

} /* end namespace td */
