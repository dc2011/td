#include "PlayerPhysicsComponent.h"
#include "../engine/Player.h"
#define PI 3.141592653589793238
#include <math.h>

#ifndef SERVER
#include "../engine/CDriver.h"
#endif

namespace td {

PlayerPhysicsComponent::PlayerPhysicsComponent()
        : collider_(td::BoxBounds(13, 3, 32, 44)) {
    accel_ = 0.3;
    decel_ = 0.6;
    maxVelocity_ = 5;
}

void PlayerPhysicsComponent::update(Unit* player)
{
    this->applyForce((Player*)player);
    this->applyVelocity((Player*)player);
    this->applyDirection((Player*)player);

#ifndef SERVER
    if (player->isDirty()) {
        td::CDriver::updateServer(player);
    }
#endif
}

/* applies velocity to position, currently moves past bounds */
void PlayerPhysicsComponent::applyVelocity(Player* player)
{
    //assuming body of player sprite is from 13,4 to 35, 44

    QPointF newPos = player->getPos() + player->getVelocity().toPointF();
    QPointF upperRight = newPos + QPointF(11, -20);
    QPointF upperLeft = newPos + QPointF(-11, -20);
    QPointF lowerRight = newPos + QPointF(11, 20);
    QPointF lowerLeft = newPos + QPointF(-11, 20);


    if (validateMovement(upperRight) && validateMovement(upperLeft)
        && validateMovement(lowerRight) && validateMovement(lowerLeft)) {
        // Determine if the Player needs to update its tile position.
        player->changeTile(newPos);
        player->setPos(newPos);
    }else{
        QVector2D temp(0, 0);
        player->setVelocity(temp);
    }
}

void PlayerPhysicsComponent::applyForce(Player* player)
{
    float velX, velY;
    QVector2D force = player->getForce();
    QVector2D vector = force * player->getVelocity();
    QVector2D tempVector = player->getVelocity();

    if (vector.x() >= 0) {
        tempVector.setX(force.x() * accel_ + tempVector.x());
    } else {
        tempVector.setX(force.x() *(accel_ + decel_) + tempVector.x());
    }

    if (vector.y() >= 0) {
        tempVector.setY(force.y() * accel_ + tempVector.y());
    } else {
        tempVector.setY(force.y() *(accel_ + decel_) + tempVector.y());
    }
    if (tempVector.length() > maxVelocity_) {
        player->getVelocity().setX(tempVector.normalized().x()*maxVelocity_);
        player->getVelocity().setY(tempVector.normalized().y()*maxVelocity_);
    } else {
        player->getVelocity().setX(tempVector.x());
        player->getVelocity().setY(tempVector.y());
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

void PlayerPhysicsComponent::applyDirection(Player* player)
{
    int angle = 0;
    int degree = 0;
    int velX = player->getVelocity().x();
    int velY = player->getVelocity().y();

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

    player->setOrientation(degree);
    //qDebug("Orientation: %d", degree);
}

bool PlayerPhysicsComponent::validateMovement(const QPointF& newPos) {
    int blockingType = 0;

    emit requestTileType(newPos.x(), newPos.y(), &blockingType);

    if (blockingType == OPEN) {
        return true;
    }

    else if (blockingType == CLOSED) {
        return false;
    }

    else {
        // TODO: This is where we will call a function to determine what areas
        // are blocked due to other blocking types or other units
        if (checkSemiBlocked(newPos, blockingType)) {
            return true;
        }
        return false;
    }
}

bool PlayerPhysicsComponent::checkSemiBlocked(QPointF pos, int type) {

    float posX = pos.x() / TILE_WIDTH;
    float posY = pos.y() / TILE_HEIGHT;

    switch(type) {
        case NORTH_WEST:
            if (posY < (TILE_WIDTH - posX)) {
                return false;
            }
            break;

        case NORTH_EAST:
            if ((posX > posY)) {
                return false;
            }
            break;

        case SOUTH_WEST:
            if ((posX < posY)) {
                return false;
            }
            break;

        case SOUTH_EAST:
            if (posY > (TILE_WIDTH - posX)) {
                return false;
            }
            break;

        default:
            break;
    }

    return true;
}

} /* end namespace td */
