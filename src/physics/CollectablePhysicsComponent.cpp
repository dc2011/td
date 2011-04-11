#include "CollectablePhysicsComponent.h"
#include "../engine/Collectable.h"
#include "../engine/Map.h"
#include "../engine/Tile.h"
#include "../engine/CDriver.h"

namespace td {

CollectablePhysicsComponent::CollectablePhysicsComponent(double velocity) {
    maxVelocity_ = accel_ = decel_ = velocity;
    duration_ = -1;
    increment_ = 0;
}

CollectablePhysicsComponent::~CollectablePhysicsComponent() {}

void CollectablePhysicsComponent::update(GameObject* collectable) {
    this->applyForce((Collectable*) collectable);
    this->applyVelocity((Collectable*) collectable);
    this->setScale((Collectable*) collectable);
}

void CollectablePhysicsComponent::applyVelocity(Collectable* collectable) {
    QPointF newPos = collectable->getPos()
                     + collectable->getVelocity().toPointF();

    collectable->setPos(newPos);
}

void CollectablePhysicsComponent::applyForce(Collectable* collectable) {
    float velX, velY;
    QVector2D force = collectable->getForce();
    QVector2D vector = force * collectable->getVelocity();
    QVector2D tempVector = collectable->getVelocity();

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
        collectable->getVelocity().setX(tempVector.normalized().x()
                                       * maxVelocity_);
        collectable->getVelocity().setY(tempVector.normalized().y()
                                       * maxVelocity_);
    } else {
        collectable->getVelocity().setX(tempVector.x());
        collectable->getVelocity().setY(tempVector.y());
    }

    if (force.x() == 0) {
        // deceleration towards 0
        if ((velX = collectable->getVelocity().x()) > 0) {
            if ((velX - decel_) < 0) {
                collectable->getVelocity().setX(0);
            } else {
                collectable->getVelocity().setX(velX - decel_);
            }
        } else if ((velX = collectable->getVelocity().x()) < 0) {
            if ((velX + decel_) > 0) {
                collectable->getVelocity().setX(0);
            } else {
                collectable->getVelocity().setX(velX + decel_);
            }
        }
    }

    if (force.y() == 0) {
        // deceleration towards 0
        if ((velY = collectable->getVelocity().y()) > 0) {
            if ((velY - decel_) < 0) {
                collectable->getVelocity().setY(0);
            } else {
                collectable->getVelocity().setY(velY - decel_);
            }
        } else if ((velY = collectable->getVelocity().y()) < 0) {
            if ((velY + decel_) > 0) {
                collectable->getVelocity().setY(0);
            } else {
                collectable->getVelocity().setY(velY + decel_);
            }
        }
    }
}

} /* end namespace td */

