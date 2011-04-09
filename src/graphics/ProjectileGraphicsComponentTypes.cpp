#include "ProjectileGraphicsComponentTypes.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* ArrowProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FireProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakProjectileGraphicsComponent::pixmapImgs_ = NULL;

ArrowProjectileGraphicsComponent::ArrowProjectileGraphicsComponent() 
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void ArrowProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_ARROW_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_ARROW;
    pixmapIndex_ = 0;
}

CannonProjectileGraphicsComponent::CannonProjectileGraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void CannonProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_CANNON_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_CANNON;
    pixmapIndex_ = 0;
}

TarProjectileGraphicsComponent::TarProjectileGraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void TarProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_TAR_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_TAR;
    pixmapIndex_ = 0;
}

FireProjectileGraphicsComponent::FireProjectileGraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void FireProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_FIRE_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE;
    pixmapIndex_ = 0;
}

FlakProjectileGraphicsComponent::FlakProjectileGraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void FlakProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_FLAK_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FLAK;
    pixmapIndex_ = 0;
}

} /* end namespace td */

