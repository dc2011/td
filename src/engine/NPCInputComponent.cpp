#include "NPCInputComponent.h"
#include "NPC.h"

NPCInputComponent::NPCInputComponent() {
    // initialize segment with first two waypoints
    // initialize NPC position to first waypoint
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
    parent_->getForce().setX(segment_.unitVector().dx());
    parent_->getForce().setY(segment_.unitVector().dy());
}

void NPCInputComponent::nextDestination() {
    segment_.setP1(parent_->getPos());
    if (segment_.length() < parent_->getVelocity().length()) {
        //segment_.setP2(); Set P2 to next waypoint
    }
}
