#include "BuildingTowerGraphicsComponent.h"
#include "../engine/BuildingTower.h"

namespace td {

BuildingTowerGraphicsComponent::BuildingTowerGraphicsComponent()
        : GraphicsComponent() {
    emit created(this);
}

BuildingTowerGraphicsComponent::~BuildingTowerGraphicsComponent() {}

QPixmap* BuildingTowerGraphicsComponent::pixmapImgs_ = NULL;

void BuildingTowerGraphicsComponent::initPixmaps() {
    if (pixmapImgs_ != NULL) {
        return;
    }

    pixmapImgs_ = new QPixmap[1];
    pixmapImgs_[0] = PIX_BUILDING_TOWER;
}

void BuildingTowerGraphicsComponent::update(GameObject* obj) {
    BuildingTower* tower = (BuildingTower*)obj;
    //if (!tower->getDirtyStatus()) {//checks if object is dirty.
    //    return;
    //}
    tower->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = tower->getPos();
    dp->moving  = 1;
    dp->scale   = 1;
    dp->degrees = 0;
    emit signalDraw(dp, this, LAYER_TOWER);
}

} /* end namespace td */

