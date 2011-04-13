#include "Driver.h"
#include "Tile.h"
#include "Collectable.h"
#include "Tower.h"
#include "BuildingTower.h"
#include "NPC.h"
#include "Resource.h"
#include "Projectile.h"
#include "Player.h"
#include "Unit.h"
#include "GameObject.h"
#include <QPointF>
#include "CDriver.h"

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
    //connect(CDriver::instance()->getMainWindow(), SIGNAL(signalAltHeld(bool)),
    //        tower->getGraphicsComponent(), SLOT(showIcons(bool)));
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
    connect(npc, SIGNAL(signalDropResource(int, QPointF, QVector2D)),
            this, SLOT(requestCollectable(int, QPointF, QVector2D)));

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

Resource* Driver::createResource(int type) {
    Resource* resource = (Resource*)mgr_->createObject(Resource::clsIdx());

    resource->setType(type);
    resource->initComponents();

    // probably won't need regular updates for resources
    //connect(gameTimer_, SIGNAL(timeout()), resource, SLOT(update()));

    return resource;
}

void Driver::sellTower(QPointF pos) {
    Tile* currentTile = gameMap_->getTile(pos.x(), pos.y());

    switch(((Tower*)currentTile->getExtension())->getType()) {
    case TOWER_ARROW:
        dropCollectables(pos, COST_ARROW_WOOD, COST_ARROW_STONE,
                COST_ARROW_BONE, COST_ARROW_OIL, 0);
        break;
    case TOWER_CANNON:
        dropCollectables(pos, COST_CANNON_WOOD, COST_CANNON_STONE,
                COST_CANNON_BONE, COST_CANNON_OIL, 0);
        break;
    case TOWER_FLAME:
        dropCollectables(pos, COST_FLAME_WOOD, COST_FLAME_STONE,
                COST_FLAME_BONE, COST_FLAME_OIL, 0);
        break;
    case TOWER_TAR:
        dropCollectables(pos, COST_TAR_WOOD, COST_TAR_STONE,
                COST_TAR_BONE, COST_TAR_OIL, 0);
        break;
    case TOWER_FLAK:
        dropCollectables(pos, COST_FLAK_WOOD, COST_FLAK_STONE,
                COST_FLAK_BONE, COST_FLAK_OIL, 0);
        break;
    }
    destroyObject(currentTile->getExtension());
    currentTile->setActionType(TILE_BUILDABLE);
}

QVector2D Driver::getRandomVector() {
    float d = ((qrand() % 1000) / 21.0) + 50;
    float x = (qrand() % 1000) - 500;
    float y = (qrand() % 1000) - 500;

    QVector2D v = QVector2D(x, y);
    v.normalize();

    return (v * d);
}

void Driver::dropCollectables(QPointF pos,
        int wood, int stone, int bone, int oil, int gem) {
    int i = 0;

    for (i = 0; i < wood; i++) {
        createCollectable(RESOURCE_WOOD, pos, getRandomVector());
    }
    for (i = 0; i < stone; i++) {
        createCollectable(RESOURCE_STONE, pos, getRandomVector());
    }
    for (i = 0; i < bone; i++) {
        createCollectable(RESOURCE_BONE, pos, getRandomVector());
    }
    for (i = 0; i < oil; i++) {
        createCollectable(RESOURCE_TAR, pos, getRandomVector());
    }
    for (i = 0; i < gem; i++) {
        createCollectable(RESOURCE_GEM, pos, getRandomVector());
    }
}

} /* end namespace td */

