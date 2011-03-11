#include "GameObject.h"

namespace td {

GameObject::GameObject() : dirty_(0), iD_(0), pos_(QPointF(0, 0)),
        orientation_(0), scale_(1), graphics_(NULL), physics_(NULL) { 
}

GameObject::~GameObject() {
    disconnect(this, SLOT(update()));
    delete physics_;
    graphics_->deleteComponent();
}

void GameObject::networkRead(td::Stream* s) {
    /* Do NOT read the object ID here.
       It has already been read by the driver! */

    dirty_ = s->readInt();

    if (dirty_ & kPosition) {
        pos_.setX(s->readFloat());
        pos_.setY(s->readFloat());
    }

    if (dirty_ & kOrientation) {
        orientation_ = s->readInt();
    }

    if (dirty_ & kScale) {
        scale_ = s->readFloat();
    }
}

void GameObject::networkWrite(td::Stream* s) {
    s->writeInt(iD_);

    s->writeInt(dirty_);

    if (dirty_ & kPosition) {
        s->writeFloat(pos_.x());
        s->writeFloat(pos_.y());
    }

    if (dirty_ & kOrientation) {
        s->writeInt(orientation_);
    }

    if (dirty_ & kScale) {
        s->writeFloat(scale_);
    }
}

} /* end namespace td */
