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
        tempPath.setLength(tempPath.length() - 5);
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
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}

bool CollectableInputComponent::validateMovement(const QPointF& newPos) {
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

    float posX = (int) pos.x() % TILE_WIDTH;
    float posY = (int) pos.y() % TILE_HEIGHT;

    switch(type) {
        case Tile::NORTH_WEST:
            if (posY > (TILE_WIDTH - posX)) {
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
            if (posY < (TILE_WIDTH - posX)) {
                return false;
            }
            break;

        default:
            break;
    }

    return true;
}

} /* end namespace td */

