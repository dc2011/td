#include "Projectile.h"
#ifndef SERVER
#include "CDriver.h"
#endif
namespace td {

Projectile::Projectile() : Unit() {
    start_ = new QPointF(0,0);
    end_ = new QPointF(0,0);
    scale_ = 0.25;
    path_ = QLineF(end_->x(), end_->y(), start_->x(), start_->y());
    this->pos_ = QPointF(0,0);
}

void Projectile::networkRead(td::Stream* s) {
    Unit::networkRead(s);

    if (dirty_ & kDamage) {
        damage_ = s->readInt();
    }

    if (dirty_ & kStartPos) {
        start_->setX(s->readFloat());
        start_->setY(s->readFloat());
    }

    if (dirty_ & kEndPos) {
        end_->setX(s->readFloat());
        end_->setY(s->readFloat());
    }
}

void Projectile::networkWrite(td::Stream* s) {
    Unit::networkWrite(s);

    if (dirty_ & kDamage) {
        s->writeInt(damage_);
    }

    if (dirty_ & kStartPos) {
        s->writeFloat(start_->x());
        s->writeFloat(start_->y());
    }

    if (dirty_ & kEndPos) {
        s->writeFloat(end_->x());
        s->writeFloat(end_->y());
    }
}

void Projectile::update() {
#ifndef SERVER
    CDriver::updateServer(this);
#endif
    input_->update();
    physics_->update(this);
    graphics_->update(this);
}

} /* end namespace td */
