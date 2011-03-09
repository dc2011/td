#include "Player.h"
#ifndef SERVER
#include "CDriver.h"
#endif
namespace td {

Player::Player() : Unit() {
    QVector2D force(0, 0);
    this->setForce(force);

    this->setPos(100, 100);
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

} /* end namespace td */
