#include "NPCInputComponent.h"
#include "../engine/NPC.h"
#include "../physics/NPCPhysicsComponent.h"

namespace td {

NPCInputComponent::NPCInputComponent() {
    // initialize segment with first two waypoints
    waypoints_ = QList<QPointF>();
    waypoints_.push_back(QPointF(888,625));
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
    // TODO: randomize force?
    QVector2D force = QVector2D((segment_.dx() / segment_.length()),
                                (segment_.dy() / segment_.length()));
    parent_->setForce(force);
}

void NPCInputComponent::nextDestination() {
    segment_.setP1(parent_->getPos());
    float maxValue = ((NPCPhysicsComponent *)parent_->
                        getPhysicsComponent())->getMaxVelocity();
    if (segment_.length() < maxValue
            && nextDest_ < waypoints_.length()) {
        segment_.setP2(waypoints_.at(nextDest_++));
    }
}

} /* end namespace td */
