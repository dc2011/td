#include "TowerGraphicsComponent.h"
#include "../engine/Tower.h"

using namespace td;

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
    tower->setToClean();
    DrawParams* dp = new DrawParams();
    dp->pos.setX(50);
    dp->pos.setY(50);
    //dp->pos     = tower->getPos();
    dp->moving  = 1;
    //player->getVelocity().length() != 0;
    //dp->scale   = tower->getScale();
    dp->degrees = 180; //tower->getOrientation();
    emit signalDraw(dp, this);
}

void TowerGraphicsComponent::initPixmaps() {
    //TODO: add animation images here
    pixmapImgs = new QPixmap[PIX_TOWER_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex++] = PIX_PLAYER_0;//PIX_TOWER_0;
    pixmapIndex = 0; //sets image back to start
}
