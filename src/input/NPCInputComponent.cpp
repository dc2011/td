#include "NPCInputComponent.h"
#include "../engine/NPC.h"
#include "../physics/NPCPhysicsComponent.h"
#include "../engine/Map.h"
#include "../engine/Driver.h"
#include "../audio/SfxManager.h"
#include <QTime>

namespace td {

NPCInputComponent::NPCInputComponent() {
    forceCounter_ = 0;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

NPCInputComponent::~NPCInputComponent() { }

void NPCInputComponent::update() {
    this->nextDestination();
    this->makeForce();
}

void NPCInputComponent::setParent(Unit *parent) {
    // Casting Unit* to NPC*.
    parent_ = (NPC*) parent;
//    nextDest_ = 0;

    connect(this, SIGNAL(deleteUnitLater(int)),
            parent_->getDriver(), SLOT(destroyObject(int)),
            Qt::QueuedConnection);
/*
    waypoints_ = parent->getDriver()->getGameMap() ->getWaypoints(WP_PTERO);
    segment_ =  QLineF(waypoints_.at(nextDest_).x(),
                       waypoints_.at(nextDest_).y(),
                       waypoints_.at(nextDest_ + 1).x(),
                       waypoints_.at(nextDest_ + 1).y());
    nextDest_++;

    parent_->setPos(segment_.p1().x(), segment_.p1().y());
*/
}
void NPCInputComponent::initWaypoints(int path) {
    nextDest_ = 0;
    waypoints_ = parent_->getDriver()->getGameMap()->getWaypoints(path);
    segment_ =  QLineF(waypoints_.at(nextDest_).x(),
                       waypoints_.at(nextDest_).y(),
                       waypoints_.at(nextDest_ + 1).x(),
                       waypoints_.at(nextDest_ + 1).y());
    nextDest_++;
    parent_->setPos(segment_.p1().x(), segment_.p1().y());
}

void NPCInputComponent::makeForce() {
    if (forceCounter_++ % 5 == 0) {
        double rx = (qrand() % 500) / 150.0;
        double ry = (qrand() % 500) / 150.0;
        QVector2D force = QVector2D(((0.2 + segment_.dx()) * rx
                    / segment_.length()),
                ((0.2 + segment_.dy()) * ry / segment_.length()));
        parent_->setForce(force);
    }
}

void NPCInputComponent::nextDestination() {
    segment_.setP1(parent_->getPos());
    float maxValue = ((NPCPhysicsComponent *)parent_->
                        getPhysicsComponent())->getMaxVelocity();
    if (segment_.length() < maxValue * 5
            && nextDest_ < waypoints_.length()) {
        segment_.setP2(waypoints_.at(nextDest_++));
    } else if (segment_.length() < maxValue * 5
            && nextDest_ >= waypoints_.length()) {
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                parent_, SLOT(update()));

        int health = parent_->getDriver()->getBaseHealth();
        health -= parent_->getDamage();
        parent_->getDriver()->setBaseHealth(health);
	PLAY_LOCAL_SFX(SfxManager::npcInBase);
        emit deleteUnitLater(parent_->getID());  
    }
}

} /* end namespace td */
