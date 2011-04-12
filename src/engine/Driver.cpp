#include "Driver.h"
#include "Collectable.h"
#include "Tower.h"
#include "NPC.h"
#include "Resource.h"
#include "Projectile.h"
#include "Unit.h"
#include "GameObject.h"
#include <QPointF>

namespace td {

Driver::Driver() : QObject(), gameMap_(NULL), gameTimer_(NULL)
{
    mgr_ = new ResManager(this);
}

Driver::~Driver()
{
    delete mgr_;
    delete gameMap_;
    delete gameTimer_;
}

void Driver::destroyObject(GameObject* obj) {
    mgr_->deleteObject(obj);
}

void Driver::destroyObject(int id) {
    GameObject* go = mgr_->findObject(id);
    if (go != NULL) {
        mgr_->deleteObject(go);
    }
}

GameObject* Driver::findObject(unsigned int id) {
    return mgr_->findObject(id);
}

Tower* Driver::createTower(int type) {
    Tower* tower = (Tower*)mgr_->createObject(Tower::clsIdx());

    tower->setType(type);
    tower->initComponents();

    connect(gameTimer_, SIGNAL(timeout()), tower, SLOT(update()));
#ifdef SERVER
    connect(tower->getPhysicsComponent(),
            SIGNAL(fireProjectile(int, QPointF, QPointF, Unit*)),
            this, SLOT(requestProjectile(int, QPointF, QPointF, Unit*)));
#endif
    return tower;
}

NPC* Driver::createNPC(int type) {
    NPC* npc = (NPC*)mgr_->createObject(NPC::clsIdx());

    npc->setType(type);
    npc->initComponents();

    //connect(gameTimer_, SIGNAL(timeout()), npc, SLOT(update()));

    return npc;
}

void Driver::requestProjectile(int projType, QPointF source,
        QPointF target, Unit* enemy) {
    Driver::createProjectile(projType, source, target,     
            enemy);
}

void Driver::requestCollectable(int projType, QPointF source, 
        QVector2D velocity) {
    Driver::createCollectable(projType, source, velocity);
}

Projectile* Driver::createProjectile(int projType, QPointF source,
        QPointF target, Unit* enemy) {
    Projectile* projectile = (Projectile*)mgr_->createObject(
            Projectile::clsIdx());
    projectile->setType(projType);
    projectile->setPath(source, target, enemy);

    projectile->initComponents();

    connect(gameTimer_,  SIGNAL(timeout()), projectile, SLOT(update()));

    return projectile;
}

Collectable* Driver::createCollectable(int collType, QPointF source, 
        QVector2D velocity) {

    Collectable* collectable = 
            (Collectable*)mgr_->createObject(Collectable::clsIdx());
    collectable->setType(collType);
    collectable->setPath(source, velocity);

    collectable->initComponents();

    connect(gameTimer_,  SIGNAL(timeout()), collectable, SLOT(update()));

    return collectable;
}

/*Resource* Driver::createResource(int type) {
}*/

} /* end namespace td */
