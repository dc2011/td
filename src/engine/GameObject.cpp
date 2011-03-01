#include "GameObject.h"

GameObject::GameObject() : pos_(QPointF(0, 0)), dirty_(0), iD_(0) { }

void GameObject::networkWrite(td::Stream* s) {
    s->writeInt(iD_);
}
