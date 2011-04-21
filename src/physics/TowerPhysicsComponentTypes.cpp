#include "TowerPhysicsComponentTypes.h"
#include "../engine/Tower.h"
#include "../graphics/TowerGraphicsComponent.h"
#define PI 3.141592653589793238

namespace td {

ArrowTowerPhysicsComponent::ArrowTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_ARROW, RADIUS_ARROW,
                PROJ_ARROW) { }

bool ArrowTowerPhysicsComponent::isValidTarget(Unit*) {
    return true;
}

CannonTowerPhysicsComponent::CannonTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_CANNON, RADIUS_CANNON,
                PROJ_CANNON) { }

bool CannonTowerPhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

FlameTowerPhysicsComponent::FlameTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAME, RADIUS_FLAME,
                PROJ_FIRE) {
    foundTarget_ = false;
    ready_ = false;
}

void FlameTowerPhysicsComponent::update(GameObject *tower){
    this->findDirectionToShoot();
    if(!foundTarget_ || !ready_) {
        return;
    }
    this->applyDirection((Tower*)tower);
    this->fire();
}

void FlameTowerPhysicsComponent::findDirectionToShoot(){
    // This tile size value is a bit flakey.
    Map* map = tower_->getDriver()->getGameMap();
    int tileSize = (map->tileWidth() + map->tileHeight()) / 2;

    // check if there's an npc currently being tracked
    if(foundTarget_) {
        return;
    }
    if(fireCountdown_ == 0) {
        ready_ = true;
    } else {
        fireCountdown_--;
        return;
    }
    projectilePath_.setP1(tower_->getPos());
    projectilePath_.setP2(tower_->getPos());
    projectilePath_.setLength(0);

    // get all npcs within range
    enemies_ = map->getUnits(tower_->getPos().x(), tower_->getPos().y(),
                             ceil((double) getRadius() / tileSize));

    if (enemies_.isEmpty()) {
        foundTarget_ = false;
        return;
    }

    QSet<Unit*>::iterator iter;

    for (iter = enemies_.begin(); iter != enemies_.end(); ++iter) {

        // this would be the place to add a priority algorithm if we need one
        // make sure that the unit is not a player
        if((((*iter)->getID()&0xFF000000)>>24) == NPC::clsIdx()) {
            if(!isValidTarget(*iter)) {
                continue;
            }
            projectilePath_.setP2((*iter)->getPos());
            // check that they're actually in range
            if (projectilePath_.length() < getRadius() - 24) {
                target_ = *iter;
                projectilePath_.setLength(getRadius() - 24);
                foundTarget_ = true;
                return;
            }
        }
    }
}

bool FlameTowerPhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

void FlameTowerPhysicsComponent::fire() {

    emit fireProjectile(projType_, tower_->getPos(), projectilePath_.p2(),
            target_);
    fireCountdown_ = fireInterval_;
    foundTarget_ = false;
#ifndef SERVER
    ((TowerGraphicsComponent*) tower_->getGraphicsComponent())->setFiring(true);
#endif
}

TarTowerPhysicsComponent::TarTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_TAR, RADIUS_TAR, PROJ_TAR)
{ }

bool TarTowerPhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

void TarTowerPhysicsComponent::update(GameObject*){
    if (fireCountdown_ != 0) {
        fireCountdown_--;
    }
    this->findTarget();
    if(target_ == NULL) {
        return;
    }
    if (fireCountdown_ == 0) {
        this->fire();
    }
}

FlakTowerPhysicsComponent::FlakTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAK, RADIUS_FLAK,
                PROJ_FLAK) { }

bool FlakTowerPhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return true;
    }
    return false;
}

} /* end namespace td */

