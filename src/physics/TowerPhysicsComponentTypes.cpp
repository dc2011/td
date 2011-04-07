#include "TowerPhysicsComponentTypes.h"

namespace td {

ArrowTowerPhysicsComponent::ArrowTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_ARROW, RADIUS_ARROW) {
}
bool ArrowTowerPhysicsComponent::isValidTarget(Unit * target) {
    return true;
}

CannonTowerPhysicsComponent::CannonTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_CANNON, RADIUS_CANNON) { 
}
bool CannonTowerPhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

FlameTowerPhysicsComponent::FlameTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAME, RADIUS_FLAME) { 
}
bool FlameTowerPhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

TarTowerPhysicsComponent::TarTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_TAR, RADIUS_TAR) { 
}
bool TarTowerPhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

FlakTowerPhysicsComponent::FlakTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAK, RADIUS_FLAK) { 
}
bool FlakTowerPhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return true;
    }
    return false;
}

} /* end namespace td */

