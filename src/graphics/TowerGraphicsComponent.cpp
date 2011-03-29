#include "TowerGraphicsComponent.h"
#include "../engine/Tower.h"

namespace td {

TowerGraphicsComponent::TowerGraphicsComponent()
        : GraphicsComponent() {
    emit created(this);
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
    emit signalDraw(dp, this, LAYER_TOWER);
}

void TowerGraphicsComponent::setIndexValue() {
    /*switch (towerType_) {
        case TOWER_ARROW:   pixmapIndex_ = 0;   break;
        case TOWER_CANNON:  pixmapIndex_ = 1;   break;
        case TOWER_TAR:     pixmapIndex_ = 2;   break;
        case TOWER_FLAME:   pixmapIndex_ = 3;   break;
        case TOWER_FLAK:    pixmapIndex_ = 4;   break;
    }*/
}

} /* end namespace td */
