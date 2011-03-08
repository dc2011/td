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
        s->write(nickname_.data());
    }
}

void Player::update() {
    if (physics_ != NULL) {
        physics_->update(this);
    }

    graphics_->update(this);
}

} /* end namespace td */
