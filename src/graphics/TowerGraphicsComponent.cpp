#include "TowerGraphicsComponent.h"
#include "../engine/Tower.h"

namespace td {

TowerGraphicsComponent::TowerGraphicsComponent()
        : GraphicsComponent() {
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
    dp->scale   = 0.25;//tower->getScale();
    dp->degrees = 0 + angle_++; //tower->getOrientation();
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

void TowerGraphicsComponent::initPixmaps() {
    //TODO: add animation images here
    pixmapImgs = new QPixmap[PIX_TOWER_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex++] = PIX_TOWER_0;
    pixmapIndex = 0; //sets image back to start
}

} /* end namespace td */
