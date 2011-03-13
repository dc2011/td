#include "TowerPhysicsComponentTypes.h"

namespace td {

ArrowTowerPhysicsComponent::ArrowTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_ARROW) { 
}

CannonTowerPhysicsComponent::CannonTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_CANNON) { 
}

FlameTowerPhysicsComponent::FlameTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAME) { 
}

TarTowerPhysicsComponent::TarTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_TAR) { 
}

FlakTowerPhysicsComponent::FlakTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAK) { 
}

} /* end namespace td */

