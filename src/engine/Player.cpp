#include "Player.h"

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
    if (physics_ != NULL) {
        physics_->update(this);
    }

    graphics_->update(this);
}

void Player::createEffect(Effect::EffectType type){
    Effect* effect = new Effect(this, type);
    effects_.push_back(effect);
    effect->apply();
}

} /* end namespace td */
