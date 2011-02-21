#include "TowerGraphicsComponent.h"
#include "../engine/Player.h"  //THIS MUST BE CHANGED TO TOWER

TowerGraphicsComponent::TowerGraphicsComponent()
        : GraphicsComponent() {
    /* Do init-type stuff here */
}

TowerGraphicsComponent::~TowerGraphicsComponent() {}

void TowerGraphicsComponent::update(GameObject* obj) {
    Player* tower = (Player*)obj; //MUST BE CHNAGED TO TOWER
    if (!tower->getDirtyStatus()) {//checks if object is dirty.
        return;
    }
    tower->setToClean();
    DrawParams* dp = new DrawParams();
    dp->pos     = tower->getPos();
    dp->moving  = 1; //is always moving
    //player->getVelocity().length() != 0;
    dp->scale   = tower->getScale(); // will likely be a constant value here
    dp->degrees = tower->getOrientation();
    emit signalDraw(dp, this);
}

void TowerGraphicsComponent::initPixmaps() {
    //TODO: add animation images here
    pixmapImgs = new QPixmap[PIX_PROJECTILE_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex++] = PIX_PROJECTILE_0;
    pixmapIndex = 0; //sets image back to start
}
