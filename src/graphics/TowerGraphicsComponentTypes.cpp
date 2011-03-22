#include "TowerGraphicsComponentTypes.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* ArrowTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlameTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakTowerGraphicsComponent::pixmapImgs_ = NULL;

void ArrowTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    //pixmapImgs_ = new QPixmap[PIX_TOWER_MAX];
    //pixmapImgs_[0] = ...;
}

void CannonTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    //pixmapImgs_ = new QPixmap[PIX_TOWER_MAX];
    //pixmapImgs_[0] = ...;
}

void TarTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    //pixmapImgs_ = new QPixmap[PIX_TOWER_MAX];
    //pixmapImgs_[0] = ...;
}

void FlameTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    //pixmapImgs_ = new QPixmap[PIX_TOWER_MAX];
    //pixmapImgs_[0] = ...;
}

void FlakTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    //pixmapImgs_ = new QPixmap[PIX_TOWER_MAX];
    //pixmapImgs_[0] = ...;
}

} /* end namespace td */
