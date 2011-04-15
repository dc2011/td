#include "TowerGraphicsComponentTypes.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* ArrowTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlameTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakTowerGraphicsComponent::pixmapImgs_ = NULL;

ArrowTowerGraphicsComponent::ArrowTowerGraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(ARROW_COLOR);
    emit created(this);
}

void ArrowTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[1];
    pixmapImgs_[0] = PIX_TOWER_ARROW;
}

CannonTowerGraphicsComponent::CannonTowerGraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(CANNON_COLOR);
    emit created(this);
}

void CannonTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[1];
    pixmapImgs_[0] = PIX_TOWER_CANNON;
}

TarTowerGraphicsComponent::TarTowerGraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(TAR_COLOR);
    emit created(this);
}

void TarTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[1];
    pixmapImgs_[0] = PIX_TOWER_TAR;
}

FlameTowerGraphicsComponent::FlameTowerGraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(FLAME_COLOR);
    emit created(this);
}

void FlameTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[1];
    pixmapImgs_[0] = PIX_TOWER_FLAME;
}

FlakTowerGraphicsComponent::FlakTowerGraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(FLAK_COLOR);
    emit created(this);
}

void FlakTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[1];
    pixmapImgs_[0] = PIX_TOWER_FLAK;
}

} /* end namespace td */
