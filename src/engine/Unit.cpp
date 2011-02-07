#include "Unit.h"

Unit::~Unit() {
    delete input_;
    delete physics_;
}

QVector2D& Unit::GetVelocity() {
    return velocity_;
}

void Unit::SetVelocity(QVector2D& velocity) {
    velocity_ = velocity;
}
