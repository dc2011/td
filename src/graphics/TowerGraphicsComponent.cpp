#include "TowerGraphicsComponent.h"
#include "../engine/Tower.h"

namespace td {

    QPixmap * TowerGraphicsComponent::pixmapImgs_ = 0;
TowerGraphicsComponent::TowerGraphicsComponent(int towerType)
        : GraphicsComponent(), towerType_(towerType) {
    emit created(this);
    /* Do init-type stuff here */
}

TowerGraphicsComponent::~TowerGraphicsComponent() {}

void TowerGraphicsComponent::update(GameObject* obj) {
    Tower* tower = (Tower*)obj;
    //if (!tower->getDirtyStatus()) {//checks if object is dirty.
    //    return;
    //}
    tower->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = tower->getPos();
    dp->moving  = 1;
    //player->getVelocity().length() != 0;
    dp->scale   = 1;//tower->getScale();
    dp->degrees = tower->getOrientation();
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

void TowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        setIndexValue();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_TOWER_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_ARROW;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_CANNON;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_TAR;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_FLAME;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_FLAK;
    setIndexValue();
}

void TowerGraphicsComponent::setIndexValue() {
    switch (towerType_) {
        case TOWER_ARROW:   pixmapIndex_ = 0;   break;
        case TOWER_CANNON:  pixmapIndex_ = 1;   break;
        case TOWER_TAR:     pixmapIndex_ = 2;   break;
        case TOWER_FLAME:   pixmapIndex_ = 3;   break;
        case TOWER_FLAK:    pixmapIndex_ = 4;   break;
    }
}

QPixmap * TowerGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

} /* end namespace td */
