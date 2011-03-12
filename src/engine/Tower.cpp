#include "Tower.h"
#ifndef SERVER
#include "CDriver.h"
#endif
#include "Effect.h"
#include "../util/defines.h"

namespace td {

void Tower::update() {

    physics_->update(this);
    graphics_->update(this);
    CDriver::updateServer(this);

#ifndef SERVER
    CDriver::updateServer(this);
#endif
}

void Tower::initComponents() {

    componentsInitialized_ = false;
}

void Tower::initComponents(int towerType) {
    QString pixmapPath;
    size_t fireInterval;

    switch (towerType) {
        case TOWER_ARROW:   
            pixmapPath = PIX_TOWER_ARROW;
            fireInterval = FIRE_INTERVAL_ARROW;
            break;
        case TOWER_CANNON:  
            pixmapPath = PIX_TOWER_CANNON;
            fireInterval = FIRE_INTERVAL_CANNON;
            break;
        case TOWER_TAR:     
            pixmapPath = PIX_TOWER_TAR;     
            fireInterval = FIRE_INTERVAL_TAR;
            break;
        case TOWER_FLAME:   
            pixmapPath = PIX_TOWER_FLAME;   
            fireInterval = FIRE_INTERVAL_FLAME;
            break;
        case TOWER_FLAK:    
            pixmapPath = PIX_TOWER_FLAK;    
            fireInterval = FIRE_INTERVAL_FLAK;
            break;
    }
    
    PhysicsComponent* physics = new TowerPhysicsComponent(fireInterval);
    this->setPhysicsComponent(physics);

    GraphicsComponent* graphics = new TowerGraphicsComponent(pixmapPath);
    this->setGraphicsComponent(graphics);
}

} // end of namespace td

