#include "NPCPhysicsComponent.h"
#include "../engine/NPC.h"
#define PI 3.141592653589793238
#include <math.h>
#include "../engine/Unit.h"
#include "../engine/Map.h"
#include "../engine/CDriver.h"

namespace td {

NPCPhysicsComponent::NPCPhysicsComponent(float a, float d, float mV)
        : accel_(a), decel_(d), maxVelocity_(mV) {}
NPCPhysicsComponent::~NPCPhysicsComponent() {}

void NPCPhysicsComponent::update(GameObject* npc)
{
    this->applyForce((NPC*)npc);
    this->applyVelocity((NPC*)npc);
    this->applyDirection((NPC*)npc);
}

/* applies velocity to position, currently moves past bounds */
void NPCPhysicsComponent::applyVelocity(NPC* npc)
{
    QPointF newPos = npc->getPos() + npc->getVelocity().toPointF();
    QPointF point;
    QVector<QPointF> points;
    QMatrix matrix = QMatrix();
    matrix.rotate(-npc->getOrientation());

    //prevent enemies from leaving the map. May not be necessary
    Map* gameMap = npc->getDriver()->getGameMap();
    Tiled::Map* tMap = gameMap->getTMap();
    int mapHeight = tMap->height();
    int mapWidth = tMap->width();
    QSize mapSize = tMap->maxTileSize();

    /*if(newPos.x() < 20){
        newPos.setX(20);
    }
    if(newPos.x() > (mapWidth * mapSize.width() - 20)){
        newPos.setX(mapWidth * mapSize.width() - 20);
    }
    if(newPos.y() < 20){
        newPos.setY(20);
    }
    if(newPos.y() > (mapHeight * mapSize.height() - 20)){
        newPos.setY(mapHeight * mapSize.height() - 20);
    }*/
    // Determine if the NPC needs to update its tile position.
    npc->changeTile(newPos);
    npc->setPos(newPos);

    //set up Vector to construct bounding Polygon
    point = QPointF(-npc->getWidth()/2, -npc->getHeight( )/2) * matrix;
    point += newPos;
    points.append(point);
    point = QPointF(npc->getWidth()/2, -npc->getHeight()/2) * matrix;
    point += newPos;
    points.append(point);
    point = QPointF(npc->getWidth()/2, npc->getHeight()/2) * matrix;
    point += newPos;
    points.append(point);
    point = QPointF(-npc->getWidth()/2, npc->getHeight()/2) * matrix;
    point += newPos;
    points.append(point);
    point = QPointF(-npc->getWidth()/2, -npc->getHeight()/2) * matrix;
    point += newPos;
    points.append(point);

    npc->setBounds(QPolygonF(points));
}

void NPCPhysicsComponent::applyForce(NPC* npc)
{
    float velX, velY;
    QVector2D force = npc->getForce();
    QVector2D vector = force * npc->getVelocity();
    QVector2D tempVector = npc->getVelocity();

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
        npc->getVelocity().setX(tempVector.normalized().x()*maxVelocity_);
        npc->getVelocity().setY(tempVector.normalized().y()*maxVelocity_);
    } else {
        npc->getVelocity().setX(tempVector.x());
        npc->getVelocity().setY(tempVector.y());
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
    float velX = npc->getVelocity().x();
    float velY = npc->getVelocity().y();

    if (velX == 0 && velY == 0) {
        return;
    }

    if (qAbs(velX) >= qAbs(velY)) {
        angle = atan(velY / velX) * (180 / PI);

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
        angle = atan(velX / velY) * (180 / PI);

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
}

} /* end namespace td */
