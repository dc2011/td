#include "TowerGraphicsComponent.h"
#include "../engine/Tower.h"

namespace td {

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

} /* end namespace td */
