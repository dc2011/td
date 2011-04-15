#include <QTime>
#include "Unit.h"
#include "CDriver.h"
#include "Map.h"
#include "Tile.h"

namespace td {

Unit::Unit(QObject* parent) : GameObject(parent), velocity_(QVector2D(0, 0)),
        force_(QVector2D(0, 0)), input_(NULL) {
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

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

QVector2D Unit::getRandomVector() {
    float d = ((qrand() % 1000) / 21.0) + 50;
    float x = (qrand() % 1000) - 500;
    float y = (qrand() % 1000) - 500;

    QVector2D v = QVector2D(x, y);
    v.normalize();

    return (v * d);
}

void Unit::changeTile(QPointF newPos){
    // Get pointer to map.
    Map* map = getDriver()->getGameMap();
    int tWidth = map->tileWidth();
    int tHeight = map->tileHeight();

    //check if changed tiles
    if ((int)getPos().x() / tWidth != (int)newPos.x() / tWidth ||
        (int)getPos().y() / tHeight != (int)newPos.y() / tHeight) {
        //remove from old tile
        map->removeUnit(getPos().x(), getPos().y(), this);
        //add to new tile
        map->addUnit(newPos.x(), newPos.y(), this);
        
    }
}

} /* end namespace td */
