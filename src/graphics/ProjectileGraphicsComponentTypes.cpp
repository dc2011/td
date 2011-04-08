#include "ProjectileGraphicsComponentTypes.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* ArrowProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FireProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakProjectileGraphicsComponent::pixmapImgs_ = NULL;

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

