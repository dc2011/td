#include "Tower.h"
#ifndef SERVER
#include "CDriver.h"
#endif
#include "Effect.h"
#include "../graphics/TowerGraphicsComponent.h"
#include "../physics/TowerPhysicsComponentTypes.h"
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

    switch (towerType) {

        case TOWER_ARROW:
            setPhysicsComponent(new ArrowTowerPhysicsComponent(this));
            //setGraphicsComponent(new ArrowTowerGraphicsComponent());
            break;
        case TOWER_CANNON:
            setPhysicsComponent(new CannonTowerPhysicsComponent(this));
            //setGraphicsComponent(new CannonTowerGraphicsComponent());
            break;
        case TOWER_FLAME:
            setPhysicsComponent(new FlameTowerPhysicsComponent(this));
            //setGraphicsComponent(new FlameTowerGraphicsComponent());
            break;
        case TOWER_TAR:
            setPhysicsComponent(new TarTowerPhysicsComponent(this));
            //setGraphicsComponent(new TarTowerGraphicsComponent());
            break;
        case TOWER_FLAK:
            setPhysicsComponent(new FlakTowerPhysicsComponent(this));
            //setGraphicsComponent(new FlakTowerGraphicsComponent());
            break;
    }
    /* TODO: remove next 2 lines and uncomment the lines in the switch statement
     * after TowerGraphicsComponentsTypes.h has been added to this branch */
    GraphicsComponent* graphics = new TowerGraphicsComponent(towerType);
    this->setGraphicsComponent(graphics);
}

} // end of namespace td

