#include "GameObject.h"

using namespace std;


QPoint GameObject::GetPos() {
    return pos_;
}

void GameObject::SetPos(QPoint p) {
    pos_.setX(p.x());
    pos_.setY(p.y());
}