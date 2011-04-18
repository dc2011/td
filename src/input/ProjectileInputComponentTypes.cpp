#include "ProjectileInputComponentTypes.h"
#include <QPointF>
#include "../engine/Projectile.h"
#include "../engine/Driver.h"
#include "../engine/CDriver.h"
#include "../engine/Map.h"
#include "../engine/EffectTypes.h"
#include "../engine/NPC.h"
#define PI 3.141592653589793238
#include <math.h>
#include "../physics/ProjectilePhysicsComponent.h"

namespace td {

void ArrowProjectileInputComponent::update() {
    if (parent_->getEnemy() != NULL) {
        QPointF* start = new QPointF(parent_->getPos().x(),
                                     parent_->getPos().y());
        QPointF* end = new QPointF(parent_->getEnemy()->getPos().x(),
                                   parent_->getEnemy()->getPos().y());
        setPath(start, end);
    }
    this->makeForce();

}

void CannonProjectileInputComponent::update(){
    this->makeForce();
}

void TarProjectileInputComponent::update(){
    this->makeForce();
}

void FlakProjectileInputComponent::update(){
    this->makeForce();
}

FireProjectileInputComponent::FireProjectileInputComponent()
    :ProjectileInputComponent() {
    duration_ = FIRE_DURATION;
    increment_ = 0;
    counter_ = 0;
}

void FireProjectileInputComponent::update(){
    this->makeForce();
}

void FireProjectileInputComponent::makeForce(){
    QVector2D force;
    Map* map = parent_->getDriver()->getGameMap();
    QSet<Unit*> npcs;
    //QLineF distance = QLineF(parent_->getPos().x(), parent_->getPos().y(),
    //                       parent_->getPath().p1().x(), parent_->getPath().p1().y());
    QPointF *end = parent_->getEndPoint();
    npcs = map->getUnits(end->x(), end->y(), 4);
    if (++increment_ == duration_) {
        if (parent_->getEnemy() != NULL) {
            disconnect(parent_->getEnemy(), SIGNAL(signalNPCDied()),
                       parent_, SLOT(enemyDied()));
        }
        disconnect(parent_->getDriver()->getTimer(), SIGNAL(timeout()),
                   parent_, SLOT(update()));
#ifndef SERVER
        if (!((CDriver*)parent_->getDriver())->isSinglePlayer()) {
            emit deleteProjectileLater(parent_->getID());
            return;
        }
#endif
        if(!npcs.empty()){
            parent_->createBounds();
            this->checkNPCCollision(npcs);
        }
        //check for collisions here
        emit deleteProjectileLater(parent_->getID());
    } else {
        force = QVector2D(parent_->getPath().unitVector().dx() * -1,
                          parent_->getPath().unitVector().dy() * -1);
        parent_->setForce(force);
        if(counter_ % 15 == 0){
            if(!npcs.empty()){
                parent_->createBounds();
                this->checkNPCCollision(npcs);
            }
        }
        counter_++;
    }
}

} /* end namespace td */
