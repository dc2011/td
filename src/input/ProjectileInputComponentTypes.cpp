#include "ProjectileInputComponentTypes.h"
#include <QPointF>
#include "../engine/Projectile.h"
#include "../engine/Driver.h"
#include "../engine/CDriver.h"
#include "../engine/Map.h"
#include "../physics/ProjectilePhysicsComponent.h"

namespace td {

void ArrowProjectileInputComponent::update() {
    if (parent_->getEnemy() != NULL) {
        QPointF* start = new QPointF(parent_->getPos().x(),
                                     parent_->getPos().y());
        QPointF* end = new QPointF(parent_->getEnemy()->getPos().x(),
                                   parent_->getEnemy()->getPos().y());
        setPath(start, end);
    }
    this->makeForce();

}

void ArrowProjectileInputComponent::makeForce(){
    QVector2D force;
    Map* map = parent_->getDriver()->getGameMap();
    QSet<Unit*> npcs;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
                             parent_->getPath().p1().x(), parent_->getPath().p1().y());
    if (distance.length() <= parent_->getVelocity().length()) {
        if (parent_->getEnemy() != NULL) {
            disconnect(parent_->getEnemy(), SIGNAL(signalNPCDied()),
                       parent_, SLOT(enemyDied()));
        }
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
#ifndef SERVER
        if (!((CDriver*)parent_->getDriver())->isSinglePlayer()) {
            emit deleteProjectileLater(parent_->getID());
            return;
        }
#endif
        QPointF *end = parent_->getEndPoint();
        npcs = map->getUnits(end->x(), end->y(), 1);
        if(!npcs.empty()){
            parent_->createBounds();
            parent_->checkNPCCollision(npcs);
        }
        //check for collisions here
        emit deleteProjectileLater(parent_->getID());
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}

void CannonProjectileInputComponent::update(){
    this->makeForce();
}

void CannonProjectileInputComponent::makeForce(){
    QVector2D force;
    Map* map = parent_->getDriver()->getGameMap();
    QSet<Unit*> npcs;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
                             parent_->getPath().p1().x(), parent_->getPath().p1().y());
    if (distance.length() <= parent_->getVelocity().length()) {
        if (parent_->getEnemy() != NULL) {
            disconnect(parent_->getEnemy(), SIGNAL(signalNPCDied()),
                       parent_, SLOT(enemyDied()));
        }
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
#ifndef SERVER
        if (!((CDriver*)parent_->getDriver())->isSinglePlayer()) {
            emit deleteProjectileLater(parent_->getID());
            return;
        }
#endif
        QPointF *end = parent_->getEndPoint();
        npcs = map->getUnits(end->x(), end->y(), 1);
        if(!npcs.empty()){
            parent_->createBounds();
            parent_->checkNPCCollision(npcs);
        }
        //check for collisions here
        emit deleteProjectileLater(parent_->getID());
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}


FireProjectileInputComponent::FireProjectileInputComponent()
    :ProjectileInputComponent() {
    duration_ = 60;
    increment_ = 0;
}

void FireProjectileInputComponent::update(){
    this->makeForce();
}

void FireProjectileInputComponent::makeForce(){
    QVector2D force;
    Map* map = parent_->getDriver()->getGameMap();
    QSet<Unit*> npcs;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
                             parent_->getPath().p1().x(), parent_->getPath().p1().y());
    if (++increment_ == duration_) {
        if (parent_->getEnemy() != NULL) {
            disconnect(parent_->getEnemy(), SIGNAL(signalNPCDied()),
                       parent_, SLOT(enemyDied()));
        }
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
#ifndef SERVER
        if (!((CDriver*)parent_->getDriver())->isSinglePlayer()) {
            emit deleteProjectileLater(parent_->getID());
            return;
        }
#endif
        QPointF *end = parent_->getEndPoint();
        npcs = map->getUnits(end->x(), end->y(), 1);
        if(!npcs.empty()){
            parent_->createBounds();
            parent_->checkNPCCollision(npcs);
        }
        //check for collisions here
        emit deleteProjectileLater(parent_->getID());
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}

void TarProjectileInputComponent::update(){
    this->makeForce();
}

void TarProjectileInputComponent::makeForce(){
    QVector2D force;
    Map* map = parent_->getDriver()->getGameMap();
    QSet<Unit*> npcs;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
                             parent_->getPath().p1().x(), parent_->getPath().p1().y());
    if (distance.length() <= parent_->getVelocity().length()) {
        if (parent_->getEnemy() != NULL) {
            disconnect(parent_->getEnemy(), SIGNAL(signalNPCDied()),
                       parent_, SLOT(enemyDied()));
        }
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
#ifndef SERVER
        if (!((CDriver*)parent_->getDriver())->isSinglePlayer()) {
            emit deleteProjectileLater(parent_->getID());
            return;
        }
#endif
        QPointF *end = parent_->getEndPoint();
        npcs = map->getUnits(end->x(), end->y(), 1);
        if(!npcs.empty()){
            parent_->createBounds();
            parent_->checkNPCCollision(npcs);
        }
        //check for collisions here
        emit deleteProjectileLater(parent_->getID());
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}

void FlakProjectileInputComponent::update(){
    this->makeForce();
}

void FlakProjectileInputComponent::makeForce(){
    QVector2D force;
    Map* map = parent_->getDriver()->getGameMap();
    QSet<Unit*> npcs;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
                             parent_->getPath().p1().x(), parent_->getPath().p1().y());
    if (distance.length() <= parent_->getVelocity().length()) {
        if (parent_->getEnemy() != NULL) {
            disconnect(parent_->getEnemy(), SIGNAL(signalNPCDied()),
                       parent_, SLOT(enemyDied()));
        }
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
#ifndef SERVER
        if (!((CDriver*)parent_->getDriver())->isSinglePlayer()) {
            emit deleteProjectileLater(parent_->getID());
            return;
        }
#endif
        QPointF *end = parent_->getEndPoint();
        npcs = map->getUnits(end->x(), end->y(), 1);
        if(!npcs.empty()){
            parent_->createBounds();
            parent_->checkNPCCollision(npcs);
        }
        //check for collisions here
        emit deleteProjectileLater(parent_->getID());
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}
} /* end namespace td */
