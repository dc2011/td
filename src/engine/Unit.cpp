#include "Unit.h"

Unit::~Unit() {
    delete input_;
    delete physics_;
}

QVector2D& Unit::getVelocity() {
    return velocity_;
}

void Unit::setVelocity(QVector2D& velocity) {
    velocity_ = velocity;
}
