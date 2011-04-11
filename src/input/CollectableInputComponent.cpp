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

    connect(this, SIGNAL(deleteCollectableLater(int)),
            parent_->getDriver(), SLOT(destroyObject(int)), 
            Qt::QueuedConnection);
}

void CollectableInputComponent::setPath(QPointF* start, QPointF* end) {
    parent_->setPos(*start);
    parent_->setStartPoint(start);
    parent_->setEndPoint(end);
    parent_->getPath().setPoints(*end, *start);
    this->applyDirection();
}

void CollectableInputComponent::applyDirection() {
    int angle = 0;
    int degree = 0;
    int projX = parent_->getPath().x1() - parent_->getPath().x2();
    int projY = parent_->getPath().y1() - parent_->getPath().y2();

    if (projX == 0 && projY == 0) {
        return;
    }

    if (qAbs(projX) >= qAbs(projY)) {
        angle = atan(projY / (float)projX) * (180 / PI);

        if (projX > 0) {
            if (projY == 0) {
                degree = 0;
            } else if (projX == projY) {
                degree = 315;
            } else if (projX == (-projY)) {
                degree = 45;
            } else if (angle < 0) {
                degree =  -angle;
            } else {
                degree = 360 - angle;
            }
        } else if (projX < 0) {
            if (projY == 0) {
                degree = 180;
            } else if (projX == projY) {
                degree = 135;
            } else if (projX == (-projY)) {
                degree = 225;
            } else {
                degree = 180 - angle;
            }
        }
    } else if (qAbs(projY) > qAbs(projX)) {
        angle = atan(projX / (float) projY) * (180 / PI);

        if (projY < 0) {
            if (projX == 0) {
                degree = 90;
            } else {
                degree = 90 + angle;
            }
        } else if (projY > 0) {
            if (projX == 0) {
                degree = 270;
            } else {
                degree = 270 + angle;
            }
        }
    }
    parent_->setOrientation(degree);
}

} /* end namespace td */

