#include "ProjectileInputComponent.h"
#include "../engine/Projectile.h"
#include "../physics/ProjectilePhysicsComponent.h"
#include "../engine/CDriver.h"
#include "../engine/Map.h"
#define PI 3.141592653589793238
#include <math.h>

namespace td {

ProjectileInputComponent::ProjectileInputComponent() {
    
    connect(this, SIGNAL(deleteProjectileLater(int)),
            CDriver::instance(), SLOT(destroyObjLocal(int)), 
            Qt::QueuedConnection);
}

ProjectileInputComponent::~ProjectileInputComponent() { }

void ProjectileInputComponent::update() {
    this->makeForce();
}

void ProjectileInputComponent::setParent(Unit *parent) {
    parent_ = (Projectile*) parent;
}

void ProjectileInputComponent::makeForce() {
    QVector2D force;
    Map* map = td::CDriver::instance()->getGameMap();
    QSet<Unit*> npcs;
    QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
               parent_->getPath().p1().x(), parent_->getPath().p1().y());
    if (distance.length() <= parent_->getVelocity().length()) {
        disconnect(CDriver::getTimer(), SIGNAL(timeout()),
                parent_, SLOT(update()));
        QPointF *end = parent_->getEndPoint();
        npcs = map->getUnits(end->x(), end->y(), 1);
        if(!npcs.empty()){
            parent_->createBounds();
            parent_->checkNPCCollision(npcs);
        }
        //check for collisions here
        emit deleteProjectileLater(parent_->getID());
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                      parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
    }
}

void ProjectileInputComponent::setPath(QPointF* start, QPointF* end) {
    parent_->setPos(*start);
    parent_->setStartPoint(start);
    parent_->setEndPoint(end);
    parent_->getPath().setPoints(*end, *start);
    this->applyDirection();
}

void ProjectileInputComponent::applyDirection() {

    int angle = 0;
    int degree = 0;
    int projX = parent_->getPath().x1() - parent_->getPath().x2();
    int projY = parent_->getPath().y1() - parent_->getPath().y2();

    if (projX == 0 && projY == 0) {
        return;
    }

    if (qAbs(projX) >= qAbs(projY)) {
        angle = atan(projY / (float)projX) * (180 / PI);

        if (projX > 0) {
            if (projY == 0) {
                degree = 0;
            } else if (projX == projY) {
                degree = 315;
            } else if (projX == (-projY)) {
                degree = 45;
            } else if (angle < 0) {
                degree =  -angle;
            } else {
                degree = 360 - angle;
            }
        } else if (projX < 0) {
            if (projY == 0) {
                degree = 180;
            } else if (projX == projY) {
                degree = 135;
            } else if (projX == (-projY)) {
                degree = 225;
            } else {
                degree = 180 - angle;
            }
        }
    } else if (qAbs(projY) > qAbs(projX)) {
        angle = atan(projX / (float) projY) * (180 / PI);

        if (projY < 0) {
            if (projX == 0) {
                degree = 90;
            } else {
                degree = 90 + angle;
            }
        } else if (projY > 0) {
            if (projX == 0) {
                degree = 270;
            } else {
                degree = 270 + angle;
            }
        }
    }
    parent_->setOrientation(degree);
}


} /* end namespace td */
