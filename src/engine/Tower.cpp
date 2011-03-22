#include "Tower.h"
#ifndef SERVER
#include "CDriver.h"
#endif
#include "Effect.h"
#include "../graphics/TowerGraphicsComponentTypes.h"
#include "../physics/TowerPhysicsComponentTypes.h"
#include "../util/defines.h"

namespace td {

void Tower::update() {
#ifndef SERVER
    if(this->isDirty()) {
        CDriver::updateServer(this);
    }
#endif
    if (physics_ != NULL) {
        physics_->update(this);
    }

    graphics_->update(this);
}

void Tower::initComponents() {
    switch (type_) {
        case TOWER_ARROW:
            setPhysicsComponent(new ArrowTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new ArrowTowerGraphicsComponent());
#endif
            break;
        case TOWER_CANNON:
            setPhysicsComponent(new CannonTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new CannonTowerGraphicsComponent());
#endif
            break;
        case TOWER_FLAME:
            setPhysicsComponent(new FlameTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new FlameTowerGraphicsComponent());
#endif
            break;
        case TOWER_TAR:
            setPhysicsComponent(new TarTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new TarTowerGraphicsComponent());
#endif
            break;
        case TOWER_FLAK:
            setPhysicsComponent(new FlakTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new FlakTowerGraphicsComponent());
#endif
            break;
    }
}

} // end of namespace td

