#include "TowerGraphicsComponent.h"
#include "../engine/Tower.h"

namespace td {

TowerGraphicsComponent::TowerGraphicsComponent(QString pixmapPath)
        : GraphicsComponent(), pixmapPath_(pixmapPath) {
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
    //TODO: add animation images here
    pixmapImgs_ = new QPixmap[PIX_TOWER_MAX];
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = pixmapPath_;
    pixmapIndex_ = 0; //sets image back to start
}

} /* end namespace td */
