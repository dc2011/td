#include "Player.h"
#include "Driver.h"

#ifndef SERVER
#    include "CDriver.h"
#endif

namespace td {

Player::Player(QObject* parent) : Unit(parent), nickname_("") {
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
    graphics_ = new PlayerGraphicsComponent();
    graphics_->update(this);
#endif
}

void Player::update() {
    if (physics_ != NULL) {
        physics_->update(this);
    }

#ifndef SERVER
    if (this->isDirty()) {
        ((CDriver*)getDriver())->updateServer(this);
    }
#endif

    graphics_->update(this);
}

void Player::createEffect(Effect::EffectType type){
    Effect* effect = new Effect(this, type);
    QObject::connect(effect, SIGNAL(effectFinished(Effect*)),
            this, SLOT(deleteEffect(Effect*)));
    connect(getDriver()->getTimer(), SIGNAL(timeout()),
            effect, SLOT(update()));

    effects_.push_back(effect);
}

void Player::deleteEffect(Effect* effect){
    effects_.removeOne(effect);
    delete effect;
}

} /* end namespace td */
