#include "ProjectileGraphicsComponent.h"
#include "../engine/Projectile.h"

namespace td {

    QPixmap * ProjectileGraphicsComponent::pixmapImgs_ = 0;

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
    dp->scale   = projectile->getScale();
    dp->degrees = projectile->getOrientation();
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

void ProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJECTILE_3_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_] = PIX_PROJECTILE_3_0;

}

QPixmap * ProjectileGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

} /* end namespace td */
