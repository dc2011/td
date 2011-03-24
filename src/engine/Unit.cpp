#include "Unit.h"
#include "CDriver.h"
#include "Map.h"
#include "Tile.h"

namespace td {

Unit::Unit(QObject* parent) : GameObject(parent), velocity_(QVector2D(0, 0)),
        force_(QVector2D(0, 0)), input_(NULL) { }

Unit::~Unit() {
    // Remove the unit from the map before deleting it
    Map* map = getDriver()->getGameMap();
    map->removeUnit(getPos().x(), getPos().y(), this);

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

void Unit::changeTile(QPointF newPos){
    //get pointer to map
    Map* map = getDriver()->getGameMap();
    //check if changed tiles
    if ((int)getPos().x() / TILE_WIDTH  != (int)newPos.x() / TILE_WIDTH ||
        (int)getPos().y() / TILE_HEIGHT != (int)newPos.y() / TILE_HEIGHT) {
        //remove from old tile
        map->removeUnit(getPos().x(), getPos().y(), this);
        //add to new tile
        map->addUnit(newPos.x(), newPos.y(), this);
        //qDebug("moving to tile: %d, %d",(int) getPos().x() / TILE_WIDTH, (int) getPos().y() / TILE_HEIGHT);
    }
}

} /* end namespace td */
