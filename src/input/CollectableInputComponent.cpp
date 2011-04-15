#include "CollectableInputComponent.h"
#include <math.h>
#include "../engine/Collectable.h"
#include "../physics/CollectablePhysicsComponent.h"
#include "../engine/Driver.h"
#include "../engine/CDriver.h"
#include "../engine/Map.h"
#include "../engine/Tile.h"
#define PI 3.141592653589793238

namespace td {

CollectableInputComponent::CollectableInputComponent() { }

CollectableInputComponent::~CollectableInputComponent() { }

void CollectableInputComponent::setParent(Unit *parent) {
    parent_ = (Collectable*) parent;
}

void CollectableInputComponent::setPath(QPointF* start, QPointF* end) {
    parent_->setPos(*start);
    parent_->setStartPoint(start);
    QLineF tempPath = QLineF(*start, *end);

    while (!validateMovement(*end)) {
        if (tempPath.length() < 5)
        {
            tempPath.setLength(0);
        }
        else
        {
            tempPath.setLength(tempPath.length() - 5);
        }
        *end = tempPath.p2();
    }

    parent_->setEndPoint(end);
    parent_->getPath().setPoints(*end, *start);
}

void CollectableInputComponent::update() {
    this->makeForce();
}

void CollectableInputComponent::makeForce(){
    QVector2D force;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
                             parent_->getPath().p1().x(),
                             parent_->getPath().p1().y());
    if (distance.length() <= parent_->getVelocity().length()) {
        if (parent_->getType() == RESOURCE_GEM) {
            parent_->setScale(GEM_SIZE);
        } else {
            parent_->setScale(RESOURCE_SIZE);
        }
        parent_->setAtEndOfPath(true);
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}

bool CollectableInputComponent::validateMovement(const QPointF& newPos) {

    int x = parent_->getDriver()->getGameMap()->getWidthInTiles();
    int y = parent_->getDriver()->getGameMap()->getHeightInTiles();
    x = x * parent_->getDriver()->getGameMap()->getTMap()->tileWidth();
    y = y * parent_->getDriver()->getGameMap()->getTMap()->tileHeight();
    x--;
    y--;

    if (newPos.x() > x || newPos.y() > y || newPos.x() < 0 || newPos.y() < 0)
    {
        return false;
    }

    int blockingType = parent_->getDriver()->getGameMap()
        ->getTile(newPos)->getType();

    if (blockingType == Tile::OPEN) {
        return true;
    }

    else if (blockingType == Tile::CLOSED) {
        return false;
    }

    else {
        // TODO: This is where we will call a function to determine what areas
        // are blocked due to other blocking types or other units
        if (checkSemiBlocked(newPos, blockingType)) {
            return true;
        }
    }
    return false;
}

bool CollectableInputComponent::checkSemiBlocked(QPointF pos, int type) {
    // Get pointer to map.
    Map* map = parent_->getDriver()->getGameMap();
    int tWidth = map->tileWidth();
    int tHeight = map->tileHeight();

    float posX = (int) pos.x() % tWidth;
    float posY = (int) pos.y() % tHeight;

    switch(type) {
        case Tile::NORTH_WEST:
            if (posY > (tWidth - posX)) {
                return false;
            }
            break;

        case Tile::NORTH_EAST:
            if ((posX < posY)) {
                return false;
            }
            break;

        case Tile::SOUTH_WEST:
            if ((posX > posY)) {
                return false;
            }
            break;

        case Tile::SOUTH_EAST:
            if (posY < (tWidth - posX)) {
                return false;
            }
            break;

        default:
            break;
    }

    return true;
}

} /* end namespace td */

