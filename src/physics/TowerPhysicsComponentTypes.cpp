#include "TowerPhysicsComponentTypes.h"

namespace td {

ArrowTowerPhysicsComponent::ArrowTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_ARROW, RADIUS_ARROW) {
}
ArrowTowerPhysicsComponent::isValidTarget(Unit * target) {
    return true;
}

CannonTowerPhysicsComponent::CannonTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_CANNON, RADIUS_CANNON) { 
}
CannonTowerPhysicsComponent::isValidTarget(Unit *) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

FlameTowerPhysicsComponent::FlameTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAME, RADIUS_FLAME) { 
}
FlameTowerPhysicsComponent::isValidTarget(Unit *) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

TarTowerPhysicsComponent::TarTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_TAR, RADIUS_TAR) { 
}
TarTowerPhysicsComponent::isValidTarget(Unit *) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

FlakTowerPhysicsComponent::FlakTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAK, RADIUS_FLAK) { 
}
FlakTowerPhysicsComponent::isValidTarget(Unit *) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return true;
    }
    return false;
}

} /* end namespace td */

