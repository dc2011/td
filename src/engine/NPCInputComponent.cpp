#include "NPCInputComponent.h"
#include "NPC.h"

NPCInputComponent::NPCInputComponent() {
    // initialize segment with first two waypoints
    waypoints_ = QList<QPointF>();
    waypoints_.push_back(QPointF(50,50));
    waypoints_.push_back(QPointF(200,50));
    waypoints_.push_back(QPointF(300,150));
    waypoints_.push_back(QPointF(350,400));
    waypoints_.push_back(QPointF(750,750));
    nextDest_ = 0;
    segment_ =  QLineF(waypoints_.at(nextDest_).x(), waypoints_.at(nextDest_++).y(),
                       waypoints_.at(nextDest_).x(), waypoints_.at(nextDest_++).y());
}

NPCInputComponent::~NPCInputComponent() { }

void NPCInputComponent::update() {
    this->nextDestination();
    this->makeForce();
}

void NPCInputComponent::setParent(Unit *parent) {
    // Casting Unit* to NPC*.
    parent_ = (NPC*) parent;
}

void NPCInputComponent::makeForce() {
    // TODO: randomize force?
    QVector2D force = QVector2D((segment_.dx() / segment_.length()), (segment_.dy() / segment_.length()));
    parent_->setForce(force);
}

void NPCInputComponent::nextDestination() {
    segment_.setP1(parent_->getPos());
    if (segment_.length() < parent_->getVelocity().length() && nextDest_ < waypoints_.length()) {
        segment_.setP2(waypoints_.at(nextDest_++));
    }
}
