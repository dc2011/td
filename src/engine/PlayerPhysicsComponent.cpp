#include "PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() : accel_(1), decel_(2), maxVelocity_(10) {}
PlayerPhysicsComponent::~PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::update(Player* player) {
    this->applyForce(player);
    this->applyVelocity(player);
}

/* applies velocity to position, currently moves past bounds */
void PlayerPhysicsComponent::applyVelocity(Player * player) {
    QPoint newPos = player->getPos() + player->getVelocity().toPoint();
    player->setPos(newPos);
}

void PlayerPhysicsComponent::applyForce(Player* player) {
    int velX, velY;
    QVector2D force = player->getForce();
    QVector2D vector = force * player->getVelocity();

    if (vector.x() >= 0) {
        player->getVelocity().setX(force.x() * accel_ + player->getVelocity().x());
        if (qAbs(vector.x()) > maxVelocity_) {
            player->getVelocity().setX(force.x() * maxVelocity_);
        }
    } else {
        player->getVelocity().setX(force.x() * (accel_ + decel_) + player->getVelocity().x());
    }
    if (vector.y() >= 0) {
        player->getVelocity().setY(force.y() * accel_ + player->getVelocity().y());
        if (qAbs(vector.y()) > maxVelocity_) {
            player->getVelocity().setY(force.y() * maxVelocity_);
        }
    } else {
        player->getVelocity().setY(force.y() * (accel_ + decel_) + player->getVelocity().y());
    }
    if (force.x() == 0) {
        // deceleration towards 0
        if ((velX = player->getVelocity().x()) > 0) {
            if ((velX - decel_) < 0) {
                player->getVelocity().setX(0);
            } else {
                player->getVelocity().setX(velX - decel_);
            }
        } else if ((velX = player->getVelocity().x()) < 0) {
            if ((velX + decel_) > 0) {
                player->getVelocity().setX(0);
            } else {
                player->getVelocity().setX(velX + decel_);
            }
        }
    }
    if (force.y() == 0) {
        // deceleration towards 0
        if ((velY = player->getVelocity().y()) > 0) {
            if ((velY - decel_) < 0) {
                player->getVelocity().setY(0);
            } else {
                player->getVelocity().setY(velY - decel_);
            }
        } else if ((velY = player->getVelocity().y()) < 0) {
            if ((velY + decel_) > 0) {
                player->getVelocity().setY(0);
            } else {
                player->getVelocity().setY(velY + decel_);
            }
        }

    }
}
