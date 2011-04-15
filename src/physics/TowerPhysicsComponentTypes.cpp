#include "TowerPhysicsComponentTypes.h"
#include "../audio/SfxManager.h"
#include "../engine/Tower.h"
#define PI 3.141592653589793238

namespace td {

ArrowTowerPhysicsComponent::ArrowTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_ARROW, RADIUS_ARROW) {
}

bool ArrowTowerPhysicsComponent::isValidTarget(Unit*) {
    return true;
}

void ArrowTowerPhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    // TODO: move to projectilePC, once the different types have been created
    PLAY_SFX(tower_, SfxManager::projectileFireArrow);
    emit fireProjectile(PROJ_ARROW, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
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

void CannonTowerPhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    // TODO: move to projectilePC, once the different types have been created
    PLAY_SFX(tower_, SfxManager::projectileFireCannon);
    emit fireProjectile(PROJ_CANNON, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

FlameTowerPhysicsComponent::FlameTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAME, RADIUS_FLAME) {
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
            if (projectilePath_.length() < getRadius()) {
                endPoint_ = *iter;
                projectilePath_.setLength(getRadius());
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

    // TODO: move to projectilePC, once the different types have been created
    PLAY_SFX(tower_, SfxManager::projectileFireFlame);
    emit fireProjectile(PROJ_FIRE, tower_->getPos(), projectilePath_.p2(),
            endPoint_);
    fireCountdown_ = fireInterval_;
    foundTarget_ = false;
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

void TarTowerPhysicsComponent::update(GameObject*){
    this->findTarget();
    this->fire();
}

void TarTowerPhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    // TODO: move to projectilePC, once the different types have been created
    PLAY_SFX(tower_, SfxManager::projectileFireTar);
    emit fireProjectile(PROJ_TAR, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
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

void FlakTowerPhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    // TODO: move to projectilePC, once the different types have been created
    PLAY_SFX(tower_, SfxManager::projectileFireFlak);
    emit fireProjectile(PROJ_FLAK, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

} /* end namespace td */

