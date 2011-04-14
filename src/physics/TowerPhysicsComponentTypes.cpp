#include "TowerPhysicsComponentTypes.h"
#include "../audio/SfxManager.h"
#include "../engine/Tower.h"
#define PI 3.141592653589793238

namespace td {

ArrowTowerPhysicsComponent::ArrowTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_ARROW, RADIUS_ARROW) { }

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
    PLAY_SFX(tower_, SfxManager::projectileFireArrow);
    emit fireProjectile(PROJ_ARROW, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

ArrowTowerL2PhysicsComponent::ArrowTowerL2PhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_ARROW_2,
                RADIUS_ARROW_2) { }

bool ArrowTowerL2PhysicsComponent::isValidTarget(Unit*) {
    return true;
}

void ArrowTowerL2PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireArrow);
    //TODO change to new upgrade projectile type
    emit fireProjectile(PROJ_ARROW, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

ArrowTowerL3PhysicsComponent::ArrowTowerL3PhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_ARROW_3,
                RADIUS_ARROW_3) { }

bool ArrowTowerL3PhysicsComponent::isValidTarget(Unit*) {
    return true;
}

void ArrowTowerL3PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireArrow);
    //TODO change to new upgrade projectile type
    emit fireProjectile(PROJ_ARROW, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

CannonTowerPhysicsComponent::CannonTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_CANNON, RADIUS_CANNON) { }

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
    PLAY_SFX(tower_, SfxManager::projectileFireCannon);
    emit fireProjectile(PROJ_CANNON, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

CannonTowerL2PhysicsComponent::CannonTowerL2PhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_CANNON_2,
                RADIUS_CANNON_2) { }

bool CannonTowerL2PhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

void CannonTowerL2PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireCannon);
    //TODO change to new upgrade projectile type
    emit fireProjectile(PROJ_CANNON, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

CannonTowerL3PhysicsComponent::CannonTowerL3PhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_CANNON_3,
                RADIUS_CANNON_3) { }

bool CannonTowerL3PhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

void CannonTowerL3PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireCannon);
    //TODO change to new upgrade projectile type
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
    if(!foundTarget_ && !ready_) {
        return;
    }
    this->applyDirection((Tower*)tower);
    this->fire();
}

void FlameTowerPhysicsComponent::findDirectionToShoot(){
    // check if there's an npc currently being tracked
    if(foundTarget_) {
        return;
    }
    if(fireCountdown_ == 0) {
        ready_ = true;
    } else {
        return;
    }
    projectilePath_.setP1(tower_->getPos());
    projectilePath_.setP2(tower_->getPos());
    projectilePath_.setLength(0);

    // get all npcs within range
    Map* map = tower_->getDriver()->getGameMap();
    enemies_ = map->getUnits(tower_->getPos().x(), tower_->getPos().y(),
                             ceil((double) getRadius() / TILE_SIZE));

    if (enemies_.isEmpty()) {
        foundTarget_ = false;
        return;
    }

    QSet<Unit*>::iterator iter;

    for (iter = enemies_.begin(); iter != enemies_.end(); ++iter) {

        // this would be the place to add a priority algorithm if we need one
        // make sure that the unit is not a player
        if((((*iter)->getID()&0xFF000000)>>24) == NPC::clsIdx()) {
            projectilePath_.setP2((*iter)->getPos());
            // check that they're actually in range
            if (projectilePath_.length() < getRadius()) {
                target_ = *iter;
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
    if (fireCountdown_ != 0) {
            fireCountdown_--;
            ready_ = false;
            return;
    }
    if(!foundTarget_) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireFlame);
    emit fireProjectile(PROJ_FIRE, tower_->getPos(), projectilePath_.p2(),
            target_);
    fireCountdown_ = fireInterval_;
    foundTarget_ = false;
}

FlameTowerL2PhysicsComponent::FlameTowerL2PhysicsComponent(Tower* tower)
        : FlameTowerPhysicsComponent(tower) {
    fireInterval_ = FIRE_INTERVAL_FLAME_2;
    radius_ = RADIUS_FLAME_2;
}

void FlameTowerL2PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
            fireCountdown_--;
            ready_ = false;
            return;
    }
    if(!foundTarget_) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireFlame);
    //TODO change to new upgrade projectile type
    emit fireProjectile(PROJ_FIRE, tower_->getPos(), projectilePath_.p2(),
            target_);
    fireCountdown_ = fireInterval_;
    foundTarget_ = false;
}

FlameTowerL3PhysicsComponent::FlameTowerL3PhysicsComponent(Tower* tower)
        : FlameTowerPhysicsComponent(tower) {
    fireInterval_ = FIRE_INTERVAL_FLAME_3;
    radius_ = RADIUS_FLAME_3;
}

void FlameTowerL3PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
            fireCountdown_--;
            ready_ = false;
            return;
    }
    if(!foundTarget_) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireFlame);
    //TODO change to new upgrade projectile type
    emit fireProjectile(PROJ_FIRE, tower_->getPos(), projectilePath_.p2(),
            target_);
    fireCountdown_ = fireInterval_;
    foundTarget_ = false;
}

TarTowerPhysicsComponent::TarTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_TAR, RADIUS_TAR) { }

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
    PLAY_SFX(tower_, SfxManager::projectileFireTar);
    emit fireProjectile(PROJ_TAR, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

TarTowerL2PhysicsComponent::TarTowerL2PhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_TAR_2, RADIUS_TAR_2) { 
}

bool TarTowerL2PhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

void TarTowerL2PhysicsComponent::update(GameObject*){
    this->findTarget();
    this->fire();
}

void TarTowerL2PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireTar);
    //TODO change to new upgrade projectile type
    emit fireProjectile(PROJ_TAR, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

TarTowerL3PhysicsComponent::TarTowerL3PhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_TAR_3, RADIUS_TAR_3) { 
}

bool TarTowerL3PhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return false;
    }
    return true;
}

void TarTowerL3PhysicsComponent::update(GameObject*){
    this->findTarget();
    this->fire();
}

void TarTowerL3PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireTar);
    //TODO change to new upgrade projectile type
    emit fireProjectile(PROJ_TAR, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

FlakTowerPhysicsComponent::FlakTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAK, RADIUS_FLAK) { }

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
    PLAY_SFX(tower_, SfxManager::projectileFireFlak);
    emit fireProjectile(PROJ_FLAK, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

FlakTowerL2PhysicsComponent::FlakTowerL2PhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAK_2, RADIUS_FLAK_2)
{ }

bool FlakTowerL2PhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return true;
    }
    return false;
}

void FlakTowerL2PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireFlak);
    //TODO change to new upgrade projectile type
    emit fireProjectile(PROJ_FLAK, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

FlakTowerL3PhysicsComponent::FlakTowerL3PhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAK_3, RADIUS_FLAK_3)
{ }

bool FlakTowerL3PhysicsComponent::isValidTarget(Unit * target) {
    if(((NPC*)target)->getType() == NPC_FLY) {
        return true;
    }
    return false;
}

void FlakTowerL3PhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    PLAY_SFX(tower_, SfxManager::projectileFireFlak);
    //TODO change to new upgrade projectile type
    emit fireProjectile(PROJ_FLAK, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

} /* end namespace td */

