#include "NPCInputComponent.h"
#include "../engine/NPC.h"
#include "../physics/NPCPhysicsComponent.h"
#include <QTime>

namespace td {

NPCInputComponent::NPCInputComponent() {
    // initialize segment with first two waypoints
    waypoints_ = QList<QPointF>();
    waypoints_.push_back(QPointF(50,50));
    waypoints_.push_back(QPointF(885,99));
    waypoints_.push_back(QPointF(136,99));
    waypoints_.push_back(QPointF(100,529));
    waypoints_.push_back(QPointF(430, 534));
    waypoints_.push_back(QPointF(718, 385));
    nextDest_ = 0;
    segment_ =  QLineF(waypoints_.at(nextDest_).x(),
                       waypoints_.at(nextDest_).y(),
                       waypoints_.at(nextDest_ + 1).x(),
                       waypoints_.at(nextDest_ + 1).y());
    nextDest_++;
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
    parent_->setPos(segment_.p1().x(), segment_.p1().y());
}

void NPCInputComponent::makeForce() {
    // TODO: apply same random force for longer time period?
    double rx = (qrand() % 500) / 50.0;
    double ry = (qrand() % 500) / 50.0;
    qDebug("rx ry, %f, %f", rx, ry);
    QVector2D force = QVector2D((segment_.dx() * rx / segment_.length()),
                                (segment_.dy() * ry / segment_.length()));
    parent_->setForce(force);
}

void NPCInputComponent::nextDestination() {
    segment_.setP1(parent_->getPos());
    float maxValue = ((NPCPhysicsComponent *)parent_->
                        getPhysicsComponent())->getMaxVelocity();
    if (segment_.length() < maxValue
            && nextDest_ < waypoints_.length()) {
        segment_.setP2(waypoints_.at(nextDest_++));
    } else if (segment_.length() < maxValue 
            && nextDest_ >= waypoints_.length()) {
       emit deleteUnitLater(parent_);  
    }
}

} /* end namespace td */
