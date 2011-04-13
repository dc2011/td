#include "PlayerPhysicsComponent.h"
#include "../engine/Player.h"
#define PI 3.141592653589793238
#include <math.h>
#include <typeinfo>
#include "../audio/SfxManager.h"
#include "../engine/Map.h"
#include "../engine/Tile.h"
#include "../engine/Driver.h"
#include "../engine/NPC.h"
#include "../engine/EffectTypes.h"
#include "../util/defines.h"

namespace td {

PlayerPhysicsComponent::PlayerPhysicsComponent() 
        : accel_(0.3), decel_(0.6), maxVelocity_(5), playCollisionSfx_(true) {
}

void PlayerPhysicsComponent::update(GameObject* player)
{
    this->applyForce((Player*)player);
    this->applyVelocity((Player*)player);
    this->applyDirection((Player*)player);

}

/* applies velocity to position, currently moves past bounds */
void PlayerPhysicsComponent::applyVelocity(Player* player)
{
    //assuming body of player sprite is from 13,4 to 35, 44

    QPointF newPos = player->getPos() + player->getVelocity().toPointF();

    if (player->getPos() == newPos) {
        return;
    }

    Map* gameMap = player->getDriver()->getGameMap();
    QSet<Tile*> targetTiles = gameMap->getTiles(newPos, 2);

    QPointF upperRight;
    QPointF upperLeft;
    QPointF lowerRight;
    QPointF lowerLeft;
    QSet<Unit*> npcs;
    double angle = player->getOrientation();
    QMatrix matrix = QMatrix();
    matrix.rotate(-angle);

    upperRight = QPointF(15, -15) * matrix;
    upperLeft =  QPointF(-5, -15) * matrix;
    lowerRight = QPointF(15, 15) * matrix;
    lowerLeft =  QPointF(-5, 15) * matrix;

    upperRight += newPos;
    upperLeft += newPos;
    lowerRight += newPos;
    lowerLeft += newPos;


    QVector<QPointF> points = QVector<QPointF>();
    points.append(upperRight);
    points.append(upperLeft);
    points.append(lowerLeft);
    points.append(lowerRight);
    points.append(upperRight);
    QPolygonF polygon = QPolygonF(points);
    bool flag = false;
    foreach (Tile* targetTile ,targetTiles){

        QPolygonF otherpolygon = targetTile->getBounds();
        if(polygon.intersected(otherpolygon).count() != 0){
            flag = true;
            break;
        }
    }

    if (!flag) {
        player->changeTile(newPos);
        player->setPos(newPos);
        player->setBounds(polygon);
        npcs = gameMap->getUnits(newPos.x(), newPos.y(), 3);
        if (npcs.size() != 1) {
            checkUnitCollision(npcs, player);
        }
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
    float velX = player->getVelocity().x();
    float velY = player->getVelocity().y();

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

    if (player->getOrientation() != degree) {
        player->setOrientation(degree);
        //qDebug("Orientation: %d", degree);
    }
}

void PlayerPhysicsComponent::checkUnitCollision(QSet<Unit*> units, Unit* player){
    QSet<Unit*>::iterator it;
    QPolygonF playerBounds;
    QPolygonF npcBounds;
    for (it = units.begin(); it != units.end(); ++it) {
        if ((((*it)->getID() & 0xFF000000)>>24) == NPC::clsIdx()) {
            playerBounds = player->getBounds();
            npcBounds = (*it)->getBounds();
            if (player->getBounds().intersected((*it)->getBounds()).count() != 0) {

                if (playCollisionSfx_) {
                    PLAY_SFX(player, SfxManager::playerHitsNpc);
                    playCollisionSfx_ = false;
                }

                //Effect::EffectType effectType = Effect::stunned;
                emit NPCPlayerCollided(EFFECT_NPCPLAYER);
                break;
            }
        } else if ((((*it)->getID() & 0xFF000000)>>24) == Collectable::clsIdx()) {
            playerBounds = player->getBounds();
            npcBounds = (*it)->getBounds();
            if (player->getBounds().intersected((*it)->getBounds()).count() != 0) {
                emit pickupCollectable(player->getPos().x(), player->getPos().y(), *it);
                break;
            }
        }
    }
}

} /* end namespace td */
