#include "Tower.h"
#ifndef SERVER
#include "CDriver.h"
#endif
#include "Effect.h"
#include "../graphics/TowerGraphicsComponent.h"
#include "../util/defines.h"

/**
// based on the number keys used to select the tower
#define TOWER_ARROW     49
#define TOWER_CANNON    50
#define TOWER_FLAME     51
#define TOWER_TAR       52
#define TOWER_FLAK      53
 */


namespace td {

void Tower::update() {
#ifndef SERVER
    CDriver::updateServer(this);
#endif
    graphics_->update(this);
    //physics_->update(this);
}

void Tower::initComponents() {
    componentsInitialized_ = false;
}

void Tower::initComponents(int towerType) {
    GraphicsComponent* graphics = new TowerGraphicsComponent(towerType);
    this->setGraphicsComponent(graphics);
}

} // end of namespace td

