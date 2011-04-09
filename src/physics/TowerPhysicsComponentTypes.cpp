#include "TowerPhysicsComponentTypes.h"
#include "../audio/SfxManager.h"
#include "../engine/Tower.h"

namespace td {

ArrowTowerPhysicsComponent::ArrowTowerPhysicsComponent(Tower* tower)
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_ARROW, RADIUS_ARROW) {
}
bool ArrowTowerPhysicsComponent::isValidTarget(Unit * target) {
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
        return;
    }
    if (target_ == NULL) {
        return;
    }
    // TODO: move to projectilePC, once the different types have been created
    //PLAY_SFX(tower_, SfxManager::projectileFireFlame);
    emit fireProjectile(PROJ_FIRE, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
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
    //PLAY_SFX(tower_, SfxManager::projectileFireFlak);
    emit fireProjectile(PROJ_FLAK, tower_->getPos(), target_->getPos(),
            target_);
    fireCountdown_ = fireInterval_;
}

} /* end namespace td */

