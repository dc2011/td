#include "Driver.h"
#include "Tower.h"
#include "BuildingTower.h"
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

void Driver::createBuildingTower(int type, QPointF pos) {
    BuildingTower* tower = (BuildingTower*)mgr_->createObject(
            BuildingTower::clsIdx());

    tower->setType(type);
    tower->initComponents();

    Tile* currentTile = gameMap_->getTile(pos.x(), pos.y());
    tower->setPos(currentTile->getPos());
    currentTile->setExtension(tower);

#ifndef SERVER
    connect(gameTimer_, SIGNAL(timeout()), tower, SLOT(update()));
#endif
    return tower;
}

void Driver::addToTower(BuildingTower* tower, Player* player) {
    int numResource = 0;

    switch (player->getResource()) {
    case RESOURCE_NONE:
        return;
    case RESOURCE_WOOD:
        numResource = tower->getWood(); 
        if (numResource > 0) {
            tower->setWood(numResource - 1);
        } else {
            return;
        }
        break;
    case RESOURCE_STONE:
        numResource = tower->getStone(); 
        if (numResource > 0) {
            tower->setStone(numResource - 1);
        } else {
            return;
        }
        break;
    case RESOURCE_BONE:
        numResource = tower->getBone(); 
        if (numResource > 0) {
            tower->setBone(numResource - 1);
        } else {
            return;
        }
        break;
    case RESOURCE_TAR:
        numResource = tower->getOil(); 
        if (numResource > 0) {
            tower->setOil(numResource - 1);
        } else {
            return;
        }
        break;
    }
#ifndef SERVER
    player->dropResource();
#else
    // send drop message
#endif
    if (tower->isDone()) {
        createTower(tower->getType(), tower->getPos());
        destroyObject(tower);
    }
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

/*Resource* Driver::createResource(int type) {
}*/

} /* end namespace td */
