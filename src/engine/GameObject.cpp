#include "GameObject.h"

GameObject::GameObject() : pos_(QPointF(0, 0)), dirty_(0), iD_(0),
        graphics_(NULL), physics_(NULL), input_(NULL) { 
}

GameObject::~GameObject() {
    delete graphics_;
    delete physics_;
    delete input_;
}

void GameObject::networkWrite(td::Stream* s) {
    s->writeInt(iD_);
}
