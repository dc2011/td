#include "ProjectileGraphicsComponent.h"
#include "../engine/Projectile.h"

namespace td {

ProjectileGraphicsComponent::ProjectileGraphicsComponent()
        : GraphicsComponent() {
    /* Do init-type stuff here */
    emit created(this);
}

ProjectileGraphicsComponent::~ProjectileGraphicsComponent() {}

void ProjectileGraphicsComponent::update(GameObject* obj) {
    Projectile* projectile = (Projectile*)obj;
    //should cast it to projectile
    if (!projectile->isDirty()) {//checks if object is dirty.
        return;
    }
    projectile->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = projectile->getPos();
    dp->moving  = 1; //is always moving
    //player->getVelocity().length() != 0;
    dp->scale   = projectile->getScale(); // will likely be a constant value here
    dp->degrees = projectile->getOrientation();
    emit signalDraw(dp, this);
}

void ProjectileGraphicsComponent::initPixmaps() {
    //TODO: add animation images here
    pixmapImgs = new QPixmap[PIX_PROJECTILE_3_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex] = PIX_PROJECTILE_3_0;

}

} /* end namespace td */
