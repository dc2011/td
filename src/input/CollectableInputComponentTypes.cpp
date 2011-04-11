#include "CollectableInputComponentTypes.h"
#include <math.h>
#include <QPointF>
#include "../engine/CDriver.h"
#include "../engine/Collectable.h"
#include "../engine/Driver.h"
#include "../engine/Map.h"
#include "../physics/CollectablePhysicsComponent.h"
#define PI 3.141592653589793238

namespace td {

void ResourceCollectableInputComponent::update() {
    this->makeForce();
}

void ResourceCollectableInputComponent::makeForce() {
    QVector2D force;
    Map* map = parent_->getDriver()->getGameMap();
    QSet<Unit*> npcs;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
                             parent_->getPath().p1().x(),
                             parent_->getPath().p1().y());
    if (distance.length() <= parent_->getVelocity().length()) {
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
#ifndef SERVER
        if (!((CDriver*)parent_->getDriver())->isSinglePlayer()) {
//            emit deleteCollectableLater(parent_->getID());
            qDebug("deleteLater");
            return;
        }
#endif
        QPointF *end = parent_->getEndPoint();
        npcs = map->getUnits(end->x(), end->y(), 1);
        if(!npcs.empty()){
            //parent_->createBounds();
            //parent_->checkNPCCollision(npcs);
        }
        emit deleteCollectableLater(parent_->getID());
        qDebug("deleteLater");
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}

void GemCollectableInputComponent::update() {
    this->makeForce();
}

void GemCollectableInputComponent::makeForce() {
    QVector2D force;
    Map* map = parent_->getDriver()->getGameMap();
    QSet<Unit*> npcs;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
                             parent_->getPath().p1().x(),
                             parent_->getPath().p1().y());
    if (distance.length() <= parent_->getVelocity().length()) {
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
#ifndef SERVER
        if (!((CDriver*)parent_->getDriver())->isSinglePlayer()) {
//            emit deleteCollectableLater(parent_->getID());
            return;
        }
#endif
        QPointF *end = parent_->getEndPoint();
        npcs = map->getUnits(end->x(), end->y(), 1);
        if(!npcs.empty()) {
            //parent_->createBounds();
            //parent_->checkNPCCollision(npcs);
        }
        emit deleteCollectableLater(parent_->getID());
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}

} /* end namespace td */

