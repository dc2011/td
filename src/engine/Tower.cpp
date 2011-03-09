#include "Tower.h"
#include "CDriver.h"
#include "Effect.h"
#include "../graphics/TowerGraphicsComponent.h"
#include "../physics/TowerPhysicsComponent.h"
#include "../util/defines.h"

namespace td {

void Tower::update() {
    graphics_->update(this);
    physics_->update(this);
    CDriver::updateServer(this);
}

void Tower::initComponents() {
    PhysicsComponent* physics = new TowerPhysicsComponent();

    this->setPhysicsComponent(physics);
    componentsInitialized_ = false;
}

void Tower::initComponents(int towerType) {
    QString pixmapPath;

    switch (towerType) {
        case TOWER_ARROW:   pixmapPath = PIX_TOWER_ARROW;   break;
        case TOWER_CANNON:  pixmapPath = PIX_TOWER_CANNON;  break;
        case TOWER_TAR:     pixmapPath = PIX_TOWER_TAR;     break;
        case TOWER_FLAME:   pixmapPath = PIX_TOWER_FLAME;   break;
        case TOWER_FLAK:    pixmapPath = PIX_TOWER_FLAK;    break;
    }
    GraphicsComponent* graphics = new TowerGraphicsComponent(pixmapPath);

    this->setGraphicsComponent(graphics);
}

} // end of namespace td

