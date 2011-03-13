#include "TowerPhysicsComponentTypes.h"

namespace td {

ArrowTowerPhysicsComponent::ArrowTowerPhysicsComponent()
        : TowerPhysicsComponent(FIRE_INTERVAL_ARROW) { 
}

CannonTowerPhysicsComponent::CannonTowerPhysicsComponent()
        : TowerPhysicsComponent(FIRE_INTERVAL_CANNON) { 
}

FlameTowerPhysicsComponent::FlameTowerPhysicsComponent()
        : TowerPhysicsComponent(FIRE_INTERVAL_FLAME) { 
}

TarTowerPhysicsComponent::TarTowerPhysicsComponent()
        : TowerPhysicsComponent(FIRE_INTERVAL_TAR) { 
}

FlakTowerPhysicsComponent::FlakTowerPhysicsComponent()
        : TowerPhysicsComponent(FIRE_INTERVAL_FLAK) { 
}

} /* end namespace td */

