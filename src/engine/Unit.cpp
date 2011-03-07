#include "Unit.h"

namespace td {

Unit::Unit() : GameObject(), velocity_(QVector2D(0, 0)),
        force_(QVector2D(0, 0)), input_(NULL) { }

Unit::~Unit() {
    delete input_;
}

void Unit::networkRead(td::Stream* s) {
    GameObject::networkRead(s);
}

void Unit::networkWrite(td::Stream* s) {
    GameObject::networkWrite(s);
}

QVector2D& Unit::getVelocity() {
    return velocity_;
}

void Unit::setVelocity(QVector2D& velocity) {
    velocity_ = velocity;
}

} /* end namespace td */
