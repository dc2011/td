#include "GameObject.h"

using namespace std;


QPoint GameObject::getPos() {
    return pos_;
}

void GameObject::setPos(QPoint p) {
    pos_.setX(p.x());
    pos_.setY(p.y());
}
