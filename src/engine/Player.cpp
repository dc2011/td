#include "Player.h"
#include "Driver.h"

namespace td {

Player::Player(QObject* parent) 
        : Unit(parent), nickname_(""), harvesting_(RESOURCE_NONE), 
          harvestCountdown_(HARVEST_COUNTDOWN) {
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
}

void Player::networkWrite(Stream* s) {
    Unit::networkWrite(s);

    if (dirty_ & kNickname) {
        s->writeInt(nickname_.length());
        s->write(nickname_.toAscii());
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
    harvesting_ = type;
    // TODO: show harvesting progress bar
}

void Player::stopHarvesting() {
    if (harvesting_ == RESOURCE_NONE) {
        return;
    }
    harvesting_ = RESOURCE_NONE;
    harvestCountdown_ = HARVEST_COUNTDOWN;
}
    
void Player::harvestResource() {
    if (--harvestCountdown_ <= 0) {
        harvestCountdown_ = HARVEST_COUNTDOWN;
        qDebug("Harvested a resource: %d", harvesting_);
        // TODO: hide harvesting progress bar
        return;
    }
    // TODO: update harvesting progress bar
}

} /* end namespace td */
