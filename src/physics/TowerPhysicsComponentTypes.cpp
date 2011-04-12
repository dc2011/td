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


void ArrowTowerPhysicsComponent::update(GameObject *tower){
    this->applyDirection((Tower*)tower);
    this->fire();
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


void CannonTowerPhysicsComponent::update(GameObject *tower){
    this->applyDirection((Tower*)tower);
    this->fire();
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
        : TowerPhysicsComponent(tower, FIRE_INTERVAL_FLAME, RADIUS_FLAME),duration_(0) {
    foundTarget_ = false;
    ready_ = false;
}

void FlameTowerPhysicsComponent::update(GameObject *tower){
    this->useDirection((Tower*)tower);
    this->applyDuration();
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
    flamePath_.setP1(tower_->getPos());
    flamePath_.setP2(tower_->getPos());
    flamePath_.setLength(0);

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
            flamePath_.setP2((*iter)->getPos());
            // check that they're actually in range
            if (flamePath_.length() < getRadius()) {
                endPoint_ = *iter;
                flamePath_.setLength(getRadius());
                foundTarget_ = true;
                return;
            }
        }
    }
}

void FlameTowerPhysicsComponent::useDirection(Tower *tower){
    this->findDirectionToShoot();
    if(!foundTarget_ && !ready_) {
        return;
    }
    int angle = 0;
    int degree = 0;
    int velX = flamePath_.p2().x() - tower->getPos().x();
    int velY = flamePath_.p2().y() - tower->getPos().y();

    if (velX == 0 && velY == 0) {
        return;
    }

    if (qAbs(velX) >= qAbs(velY)) {
        angle = atan(velY / (float)velX) * (180 / PI);

        if (velX > 0) {
            if (velY == 0) {
                degree = 0;
            } else if (velX == velY) {
                degree = 315;
            } else if (velX == (-velY)) {
                degree = 45;
            } else if (angle < 0) {
                degree =  (-angle);
            } else {
                degree = 360 - angle;
            }
        } else if (velX < 0) {
            if (velY == 0) {
                degree = 180;
            } else if (velX == velY) {
                degree = 135;
            } else if (velX == (-velY)) {
                degree = 225;
            } else {
                degree = 180 - angle;
            }
        }
    } else if (qAbs(velY) > qAbs(velX)) {
        angle = atan(velX / (float) velY) * (180 / PI);

        if (velY < 0) {
            if (velX == 0) {
                degree = 90;
            } else {
                degree = 90 + angle;
            }
        } else if (velY > 0) {
            if (velX == 0) {
                degree = 270;
            } else {
                degree = 270 + angle;
            }
        }
    }
    tower->setOrientation(degree);
}

void FlameTowerPhysicsComponent::applyDuration(){

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
    // TODO: move to projectilePC, once the different types have been created
    PLAY_SFX(tower_, SfxManager::projectileFireFlame);
    emit fireProjectile(PROJ_FIRE, tower_->getPos(), flamePath_.p2(),
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


void TarTowerPhysicsComponent::update(GameObject *tower){
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


void FlakTowerPhysicsComponent::update(GameObject *tower){
    this->applyDirection((Tower*)tower);
    this->fire();
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

