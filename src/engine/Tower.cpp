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

#ifndef SERVER
    CDriver::updateServer(this);
#endif
}

void Tower::initComponents() {

    componentsInitialized_ = false;
}

void Tower::initComponents(int towerType) {

    PhysicsComponent* physics = new TowerPhysicsComponent(0);
    this->setPhysicsComponent(physics);

    GraphicsComponent* graphics = new TowerGraphicsComponent(towerType);
    this->setGraphicsComponent(graphics);
}

} // end of namespace td

