#include "NPCPhysicsComponent.h"
#include "NPC.h"
#define PI 3.141592653589793238
#include <math.h>
NPCPhysicsComponent::NPCPhysicsComponent()
        : accel_(1), decel_(2), maxVelocity_(10) {}
NPCPhysicsComponent::~NPCPhysicsComponent() {}

void NPCPhysicsComponent::update(Unit* npc)
{
    this->applyForce((NPC*)npc);
    this->applyVelocity((NPC*)npc);
    this->applyDirection((NPC*)npc);
}

/* applies velocity to position, currently moves past bounds */
void NPCPhysicsComponent::applyVelocity(NPC* npc)
{
    QPointF newPos = npc->getPos() + npc->getVelocity().toPointF();
    npc->setPos(newPos);
}

void NPCPhysicsComponent::applyForce(NPC* npc)
{
    float velX, velY;
    QVector2D force = npc->getForce();
    QVector2D vector = force * npc->getVelocity();

    if (vector.x() >= 0) {
        npc->getVelocity().setX(force.x() * accel_ +
                                   npc->getVelocity().x());
        if (qAbs(vector.x()) > maxVelocity_) {
            npc->getVelocity().setX(force.x() * maxVelocity_);
        }
    } else {
        npc->getVelocity().setX(force.x() *(accel_ + decel_) +
                                   npc->getVelocity().x());
    }

    if (vector.y() >= 0) {
        npc->getVelocity().setY(force.y() * accel_ +
                                   npc->getVelocity().y());

        if (qAbs(vector.y()) > maxVelocity_) {
            npc->getVelocity().setY(force.y() * maxVelocity_);
        }
    } else {
        npc->getVelocity().setY(force.y() *(accel_ + decel_) +
                                   npc->getVelocity().y());
    }

    if (force.x() == 0) {
        // deceleration towards 0
        if ((velX = npc->getVelocity().x()) > 0) {
            if ((velX - decel_) < 0) {
                npc->getVelocity().setX(0);
            } else {
                npc->getVelocity().setX(velX - decel_);
            }
        } else if ((velX = npc->getVelocity().x()) < 0) {
            if ((velX + decel_) > 0) {
                npc->getVelocity().setX(0);
            } else {
                npc->getVelocity().setX(velX + decel_);
            }
        }
    }

    if (force.y() == 0) {
        // deceleration towards 0
        if ((velY = npc->getVelocity().y()) > 0) {
            if ((velY - decel_) < 0) {
                npc->getVelocity().setY(0);
            } else {
                npc->getVelocity().setY(velY - decel_);
            }
        } else if ((velY = npc->getVelocity().y()) < 0) {
            if ((velY + decel_) > 0) {
                npc->getVelocity().setY(0);
            } else {
                npc->getVelocity().setY(velY + decel_);
            }
        }
    }
}

void NPCPhysicsComponent::applyDirection(NPC* npc)
{
    int angle = 0;
    int degree = 0;
    int velX = npc->getVelocity().x();
    int velY = npc->getVelocity().y();

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

    npc->setOrientation(degree);
    qDebug("Orientation: %d", degree);
}
