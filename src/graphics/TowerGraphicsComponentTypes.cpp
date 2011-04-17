#include "TowerGraphicsComponentTypes.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* ArrowTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* ArrowTowerL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* ArrowTowerL3GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonTowerL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonTowerL3GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarTowerL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarTowerL3GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlameTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlameTowerL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlameTowerL3GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakTowerGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakTowerL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakTowerL3GraphicsComponent::pixmapImgs_ = NULL;

ArrowTowerGraphicsComponent::ArrowTowerGraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(ARROW_COLOR);
    emit created(this);
}

void ArrowTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_ARROW;
    pixmapImgs_[1] = PIX_TOWER_ARROW_FIRE;
}

ArrowTowerL2GraphicsComponent::ArrowTowerL2GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(250,128,114));
    emit created(this);
}

void ArrowTowerL2GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_ARROW_2;
    pixmapImgs_[1] = PIX_TOWER_ARROW_FIRE_2;
}

ArrowTowerL3GraphicsComponent::ArrowTowerL3GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(233,150,122));
    emit created(this);
}

void ArrowTowerL3GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_ARROW_3;
    pixmapImgs_[1] = PIX_TOWER_ARROW_FIRE_3;
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

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_CANNON;
    pixmapImgs_[1] = PIX_TOWER_CANNON_FIRE;
}

CannonTowerL2GraphicsComponent::CannonTowerL2GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(238,130,238));
    emit created(this);
}

void CannonTowerL2GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_CANNON_2;
    pixmapImgs_[1] = PIX_TOWER_CANNON_FIRE_2;
}

CannonTowerL3GraphicsComponent::CannonTowerL3GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(221,160,221));
    emit created(this);
}

void CannonTowerL3GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_CANNON_3;
    pixmapImgs_[1] = PIX_TOWER_CANNON_FIRE_3;
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

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_TAR;
    pixmapImgs_[1] = PIX_TOWER_TAR_FIRE_2;
}

TarTowerL2GraphicsComponent::TarTowerL2GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(0,0,238));
    emit created(this);
}

void TarTowerL2GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_TAR_2;
    pixmapImgs_[1] = PIX_TOWER_TAR_FIRE_2;
}

TarTowerL3GraphicsComponent::TarTowerL3GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(0,0,205));
    emit created(this);
}

void TarTowerL3GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_TAR_3;
    pixmapImgs_[1] = PIX_TOWER_TAR_FIRE_3;
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

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_FLAME;
    pixmapImgs_[1] = PIX_TOWER_FLAME_FIRE;
}

FlameTowerL2GraphicsComponent::FlameTowerL2GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(238,0,0));
    emit created(this);
}

void FlameTowerL2GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_FLAME_2;
    pixmapImgs_[1] = PIX_TOWER_FLAME_FIRE_2;
}

FlameTowerL3GraphicsComponent::FlameTowerL3GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(178,34,34));
    emit created(this);
}

void FlameTowerL3GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_FLAME_3;
    pixmapImgs_[1] = PIX_TOWER_FLAME_FIRE_3;
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

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_FLAK;
    pixmapImgs_[1] = PIX_TOWER_FLAK_FIRE;
}

FlakTowerL2GraphicsComponent::FlakTowerL2GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(124,252,0));
    emit created(this);
}

void FlakTowerL2GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_FLAK_2;
    pixmapImgs_[1] = PIX_TOWER_FLAK_FIRE_2;
}

FlakTowerL3GraphicsComponent::FlakTowerL3GraphicsComponent()
        : TowerGraphicsComponent() {
    initRangeCircle(QColor(0,255,127));
    emit created(this);
}

void FlakTowerL3GraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[2];
    pixmapImgs_[0] = PIX_TOWER_FLAK_3;
    pixmapImgs_[1] = PIX_TOWER_FLAK_FIRE_3;
}

} /* end namespace td */
