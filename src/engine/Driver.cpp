#include "Driver.h"
#include "Tile.h"
#include "Tower.h"
#include "BuildingTower.h"
#include "NPC.h"
#include "Resource.h"
#include "Projectile.h"
#include "Player.h"
#include "Unit.h"
#include "GameObject.h"
#include <QPointF>

namespace td {

Driver::Driver() : QObject(), gameMap_(NULL), gameTimer_(NULL), baseHealth_(100)
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
    if (go != NULL && go != (GameObject*)-1) {
        mgr_->deleteObject(go);
    }
}

GameObject* Driver::findObject(unsigned int id) {
    GameObject* obj =  mgr_->findObject(id);

    if (obj == (GameObject*)-1) {
        return NULL;
    }

    return obj;
}

Tower* Driver::createTower(int type, QPointF pos) {
    Tower* tower = (Tower*)mgr_->createObject(Tower::clsIdx());

    tower->setType(type);
    tower->initComponents();

    Tile* currentTile = gameMap_->getTile(pos.x(), pos.y());
    tower->setPos(currentTile->getPos());
    currentTile->setExtension(tower);
    currentTile->setActionType(TILE_BUILT);

    connect(gameTimer_, SIGNAL(timeout()), tower, SLOT(update()));
    connect(tower->getPhysicsComponent(),
            SIGNAL(fireProjectile(int, QPointF, QPointF, Unit*)),
            this, SLOT(requestProjectile(int, QPointF, QPointF, Unit*)));

    return tower;
}

BuildingTower* Driver::createBuildingTower(int type, QPointF pos) {
    BuildingTower* tower = (BuildingTower*)mgr_->createObject(
            BuildingTower::clsIdx());

    tower->setType(type);
    tower->initComponents();

    Tile* currentTile = gameMap_->getTile(pos.x(), pos.y());
    tower->setPos(currentTile->getPos());
    currentTile->setExtension(tower);
    currentTile->setActionType(TILE_BUILDING);

#ifndef SERVER
    connect(gameTimer_, SIGNAL(timeout()), tower, SLOT(update()));
    connect(mainWindow_, SIGNAL(signalAltHeld(bool)),
            tower->getGraphicsComponent(), SLOT(showIcons(bool)));
#endif

    return tower;
}

bool Driver::addToTower(BuildingTower* tower, Player* player) {
    int numResource = 0;

    switch (player->getResource()) {
    case RESOURCE_NONE:
        return false;
    case RESOURCE_WOOD:
        numResource = tower->getWood(); 
        if (numResource > 0) {
            tower->setWood(numResource - 1);
        } else {
            return false;
        }
        break;
    case RESOURCE_STONE:
        numResource = tower->getStone(); 
        if (numResource > 0) {
            tower->setStone(numResource - 1);
        } else {
            return false;
        }
        break;
    case RESOURCE_BONE:
        numResource = tower->getBone(); 
        if (numResource > 0) {
            tower->setBone(numResource - 1);
        } else {
            return false;
        }
        break;
    case RESOURCE_TAR:
        numResource = tower->getOil(); 
        if (numResource > 0) {
            tower->setOil(numResource - 1);
        } else {
            return false;
        }
        break;
    }

    return true;
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

Resource* Driver::createResource(int type) {
    Resource* resource = (Resource*)mgr_->createObject(Resource::clsIdx());

    resource->setType(type);
    resource->initComponents();

    // probably won't need regular updates for resources
    //connect(gameTimer_, SIGNAL(timeout()), resource, SLOT(update()));

    return resource;
}

} /* end namespace td */
