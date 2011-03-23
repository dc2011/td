#include "NPCInputComponent.h"
#include "../engine/NPC.h"
#include "../physics/NPCPhysicsComponent.h"
#include "../engine/CDriver.h"
#include "../engine/Map.h"
#include <QTime>

namespace td {

NPCInputComponent::NPCInputComponent() {
    nextDest_ = 0;
    forceCounter_ = 0;

    waypoints_ = CDriver::instance()->getGameMap()->getWaypoints(WP_PTERO);
    segment_ =  QLineF(waypoints_.at(nextDest_).x(),
                       waypoints_.at(nextDest_).y(),
                       waypoints_.at(nextDest_ + 1).x(),
                       waypoints_.at(nextDest_ + 1).y());
    nextDest_++;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    
    connect(this, SIGNAL(deleteUnitLater(int)),
            CDriver::instance(), SLOT(deadNPC(int)), Qt::QueuedConnection);
}

NPCInputComponent::~NPCInputComponent() { }

void NPCInputComponent::update() {
    this->nextDestination();
    this->makeForce();
}

void NPCInputComponent::setParent(Unit *parent) {
    // Casting Unit* to NPC*.
    parent_ = (NPC*) parent;
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
        disconnect(CDriver::getTimer(), SIGNAL(timeout()),
                parent_, SLOT(update()));
        // TODO: damage players' base
        emit deleteUnitLater(parent_->getID());  
    }
}

} /* end namespace td */
