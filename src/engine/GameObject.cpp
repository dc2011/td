#include "GameObject.h"
#include "Driver.h"
namespace td {

GameObject::GameObject(QObject* parent) : QObject(parent), dirty_(0), iD_(0),
        pos_(QPointF(0, 0)), orientation_(0), scale_(1),
        graphics_(NULL), physics_(NULL) { 
}

GameObject::~GameObject() {
    disconnect(this, SLOT(update()));
    delete physics_;
    if (graphics_ != NULL) {
        graphics_->deleteComponent();
    }
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

void GameObject::setPos(QPointF& p) {
    int x = getDriver()->getGameMap()->getWidthInTiles();
    int y = getDriver()->getGameMap()->getHeightInTiles();
    x = x * getDriver()->getGameMap()->getTMap()->tileWidth();
    y = y * getDriver()->getGameMap()->getTMap()->tileHeight();
    x-=20;
    y-=20;
    if(p.x() < 20) {
        p.setX(20);
    }
    if(p.y() < 20) {
        p.setY(20);
    }
    if(p.x() > x) {
        p.setX(x);
    }
    if(p.y() > y) {
        p.setY(y);
    }
    pos_.setX(p.x());
    pos_.setY(p.y());
    setDirty(kPosition);
    //qDebug("Pos: (%.2f, %.2f)", (float) pos_.x(), (float) pos_.y());
}

void GameObject::setPos(float x, float y) {
    int mx = getDriver()->getGameMap()->getWidthInTiles();
    int my = getDriver()->getGameMap()->getHeightInTiles();
    mx = mx * getDriver()->getGameMap()->getTMap()->tileWidth();
    my = my * getDriver()->getGameMap()->getTMap()->tileHeight();
    mx-=20;
    my-=20;
    if(x < 20) {
        x = 20;
    }
    if(y < 20) {
        y = 20;
    }
    if(x > mx) {
        x = mx;
    }
    if(y > my) {
        y = my;
    }
    pos_.setX(x);
    pos_.setY(y);
    setDirty(kPosition);
}
} /* end namespace td */
