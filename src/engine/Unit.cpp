#include "Unit.h"

Unit::Unit() : GameObject(), velocity_(QVector2D(0, 0)),
        force_(QVector2D(0, 0)), orientation_(0), scale_(1) { }

void Unit::networkRead(td::Stream* s) {
    float x = s->readFloat();
    float y = s->readFloat();
    this->setPos(x, y);

    this->setOrientation(s->readInt());

    this->setScale(s->readFloat());
}

void Unit::networkWrite(td::Stream* s) {
    GameObject::networkWrite(s);

    s->writeFloat(this->getPos().x());
    s->writeFloat(this->getPos().y());

    s->writeInt(this->getOrientation());

    s->writeFloat(this->getScale());
}

QVector2D& Unit::getVelocity() {
    return velocity_;
}

void Unit::setVelocity(QVector2D& velocity) {
    velocity_ = velocity;
}
