#include "CollectablePhysicsComponent.h"
#include "../engine/Collectable.h"
#include "../engine/Map.h"
#include "../engine/Tile.h"
#include "../engine/CDriver.h"

namespace td {

CollectablePhysicsComponent::CollectablePhysicsComponent() {
    maxVelocity_ = accel_ = decel_ = COLLECTABLE_VELOCITY;
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
    QPointF point;
    QVector<QPointF> points;
    QMatrix matrix = QMatrix();
    matrix.rotate(-collectable->getOrientation());

    //set up Vector to construct bounding Polygon
    point = QPointF(-collectable->getWidth()/2, -collectable->getHeight( )/2) * matrix;
    point += newPos;
    points.append(point);
    point = QPointF(collectable->getWidth()/2, -collectable->getHeight()/2) * matrix;
    point += newPos;
    points.append(point);
    point = QPointF(collectable->getWidth()/2, collectable->getHeight()/2) * matrix;
    point += newPos;
    points.append(point);
    point = QPointF(-collectable->getWidth()/2, collectable->getHeight()/2) * matrix;
    point += newPos;
    points.append(point);
    point = QPointF(-collectable->getWidth()/2, -collectable->getHeight()/2) * matrix;
    point += newPos;
    points.append(point);

    collectable->setPos(newPos);
    collectable->setBounds(QPolygonF(points));
}

void CollectablePhysicsComponent::setScale(Collectable *collectable) {
    if (duration_ < 0) {
        duration_ = collectable->getPath().length() / maxVelocity_ ;
        increment_ = 0;
    }
    if ((increment_++ < (duration_ / 3)) || (increment_ > (duration_ * 0.75)
                && increment_ < (duration_ * 0.875))) {
        collectable->setScale(collectable->getScale() + 0.1);
    } else if (increment_ < duration_) {
        if (increment_ >= (duration_ * 0.75)) {
            maxVelocity_ = COLLECTABLE_VELOCITY / 3;
        }
        if (collectable->getType() == RESOURCE_GEM) {
            collectable->setScale(qMax(collectable->getScale() - 0.1,
                        GEM_SIZE));
        } else {
            collectable->setScale(qMax(collectable->getScale() - 0.1,
                        RESOURCE_SIZE));
        }
    }
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

