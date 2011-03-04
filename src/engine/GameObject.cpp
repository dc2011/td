#include "GameObject.h"

GameObject::GameObject() : pos_(QPointF(0, 0)), dirty_(0), iD_(0),
        orientation_(0), scale_(1), graphics_(NULL), physics_(NULL) { 
}

GameObject::~GameObject() {
    delete graphics_;
    delete physics_;
}

void GameObject::networkRead(td::Stream* s) {
    /* Do NOT read the object ID here.
       It has already been read by the driver! */

    tmpDirty_ = s->readInt();

    if (tmpDirty_ & kPosition) {
        pos_.setX(s->readFloat());
        pos_.setY(s->readFloat());
    }

    if (tmpDirty_ & kOrientation) {
        orientation_ = s->readInt();
    }

    if (tmpDirty_ & kScale) {
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
