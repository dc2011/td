#include "ProjectileGraphicsComponent.h"
#include "../engine/Projectile.h"

namespace td {

ProjectileGraphicsComponent::~ProjectileGraphicsComponent() {}

void ProjectileGraphicsComponent::update(GameObject* obj) {
    Projectile* projectile = (Projectile*)obj;
    //should cast it to projectile
    if (!projectile->isDirty()) {
        return;
    }
    projectile->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = projectile->getPos();
    dp->moving  = 1; //is always moving
    //player->getVelocity().length() != 0;
    dp->scale   = projectile->getScale();
    dp->degrees = projectile->getOrientation();
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

} /* end namespace td */
