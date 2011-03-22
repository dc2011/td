#include "Player.h"
#ifndef SERVER
#include "CDriver.h"
#endif
namespace td {

Player::Player() : Unit(), nickname_("") {
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

void Player::update() {
#ifndef SERVER
    if(this->isDirty()) {
        CDriver::updateServer(this);
    }
#endif
    if (physics_ != NULL) {
        physics_->update(this);
    }

    graphics_->update(this);
}

void Player::createEffect(Effect::EffectType type){
    Effect* effect = new Effect(this, type);
    QObject::connect(effect, SIGNAL(effectFinished(Effect*)),
            this, SLOT(deleteEffect(Effect*)));
#ifndef SERVER
    QObject::connect(CDriver::getTimer(), SIGNAL(timeout()),
            effect, SLOT(update()));
#endif

    effects_.push_back(effect);
}

void Player::deleteEffect(Effect* effect){
    effects_.removeOne(effect);
    delete effect;
}

} /* end namespace td */
