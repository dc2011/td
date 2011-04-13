#include "CollectableInputComponent.h"
#include <math.h>
#include "../engine/Collectable.h"
#include "../physics/CollectablePhysicsComponent.h"
#include "../engine/Driver.h"
#include "../engine/CDriver.h"
#include "../engine/Map.h"
#define PI 3.141592653589793238

namespace td {

CollectableInputComponent::CollectableInputComponent() { }

CollectableInputComponent::~CollectableInputComponent() { }

void CollectableInputComponent::setParent(Unit *parent) {
    parent_ = (Collectable*) parent;
}

void CollectableInputComponent::setPath(QPointF* start, QPointF* end) {
    parent_->setPos(*start);
    parent_->setStartPoint(start);
    parent_->setEndPoint(end);
    parent_->getPath().setPoints(*end, *start);
}

void CollectableInputComponent::update() {
    this->makeForce();
}

void CollectableInputComponent::makeForce(){
    QVector2D force;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
                             parent_->getPath().p1().x(),
                             parent_->getPath().p1().y());
    if (distance.length() <= parent_->getVelocity().length()) {
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}

} /* end namespace td */

