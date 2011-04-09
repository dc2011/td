#include "Player.h"
#include "Driver.h"
#include "../audio/SfxManager.h"

namespace td {

Player::Player(QObject* parent) 
        : Unit(parent), nickname_(""), harvesting_(RESOURCE_NONE), 
          harvestCountdown_(HARVEST_COUNTDOWN), resource_(RESOURCE_NONE) {
    QVector2D force(0, 0);
    this->setForce(force);

    this->setPos(100, 100);
}

void Player::networkRead(Stream* s) {
    Unit::networkRead(s);

    if (dirty_ & kNickname) {
        int len = s->readInt();
        nickname_ = QString(s->read(len));
    }
    if (dirty_ & kResource) {
        resource_ = s->readInt();
    }
}

void Player::networkWrite(Stream* s) {
    Unit::networkWrite(s);

    if (dirty_ & kNickname) {
        s->writeInt(nickname_.length());
        s->write(nickname_.toAscii());
    }
    if (dirty_ & kResource) {
        s->writeInt(resource_);
    }
}

void Player::initComponents() {
#ifndef SERVER
    /* Client-side has a Graphics Component */
    graphics_ = new PlayerGraphicsComponent(nickname_);
    graphics_->update(this);
#endif
}

void Player::update() {
    if (physics_ != NULL) {
        physics_->update(this);
    }
    if (isDirty()) {
        getDriver()->updateRT(this);
    }
    if (graphics_ != NULL) {
        graphics_->update(this);
    }
    if (harvesting_ != RESOURCE_NONE) {
        harvestResource();
    }

    // Updating effects for player position
    //if (getDriver()->getGameMap()->getTile(getPos())->getAttributes())
//    if(getDriver()->getMap()->getTile(getPos())->getEffect()) {
//        createEffect(new PlayerTerrainEffect(this));
//    }
}

void Player::createEffect(Effect* effect){
    QObject::connect(effect, SIGNAL(effectFinished(Effect*)),
            this, SLOT(deleteEffect(Effect*)));
    connect(getDriver()->getTimer(), SIGNAL(timeout()),
            effect, SLOT(update()));

    effects_.push_back(effect);
}

void Player::deleteEffect(Effect* effect){
    effects_.removeOne(effect);
    if (effects_.empty()) {
        emit signalEmptyEffectList();
    }
    delete effect;
}

void Player::startHarvesting(int type) {
    if (resource_ != RESOURCE_NONE) {
        qDebug("Player::startHarvesting(); already carrying a resource");
        return;
    }
    harvesting_ = type;
    emit signalPlayerMovement(false);
    qDebug("Player::startHarvesting(); resource %d", harvesting_);
    // TODO: show harvesting progress bar

    switch (type) {
        case RESOURCE_WOOD:
            PLAY_LOCAL_SFX(SfxManager::resourceWood);
            break;
        case RESOURCE_STONE:
            PLAY_LOCAL_SFX(SfxManager::resourceStone);
            break;
        case RESOURCE_BONE:
            PLAY_LOCAL_SFX(SfxManager::resourceBone);
            break;
        case RESOURCE_TAR:
            PLAY_LOCAL_SFX(SfxManager::resourceTar);
            break;
    }
}

void Player::stopHarvesting() {
    if (harvesting_ == RESOURCE_NONE) {
        return;
    }
    harvesting_ = RESOURCE_NONE;
    harvestCountdown_ = HARVEST_COUNTDOWN;
    emit signalPlayerMovement(true);
}

void Player::dropResource() {
    if (resource_ == RESOURCE_NONE) {
        return;
    }
    // TODO: create resource object on current tile
    qDebug("Player::dropResource(); dropped resource");
    resource_ = RESOURCE_NONE;
    // TODO: hide resource carrying indicator
}
    
void Player::harvestResource() {
    if (--harvestCountdown_ <= 0) {
        resource_ = harvesting_;
        harvestCountdown_ = HARVEST_COUNTDOWN;
        qDebug("Player::harvestResource(); resource: %d", harvesting_);
        // TODO: hide harvesting progress bar
        // TODO: add resource carrying indicator
        stopHarvesting();
        return;
    }
    // TODO: update harvesting progress bar
}

} /* end namespace td */
