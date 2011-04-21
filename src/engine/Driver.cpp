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

Driver::Driver() : QObject(), gameMap_(NULL), gameTimer_(NULL),
        baseHealth_(100), gemCount_(0)
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

void Driver::requestCollectable(int, QPointF, QVector2D) {
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
    if (currentTile->getExtension() == NULL) {
        return;
    }
    int type = ((Tower*)currentTile->getExtension())->getType();
    int towerType = type >> 4;

    if (towerType == 0) {
        switch (type) {
            case TOWER_ARROW_1:
                dropCollectables(pos, COST_ARROW_WOOD, COST_ARROW_STONE,
                        COST_ARROW_BONE, COST_ARROW_OIL, 0);
                break;
            case TOWER_ARROW_2:
                dropCollectables(pos, COST_ARROW_WOOD, COST_ARROW_STONE,
                        COST_ARROW_BONE, COST_ARROW_OIL, COST_TOWER_UPGRADE);
                break;
            case TOWER_ARROW_3:
                dropCollectables(pos, COST_ARROW_WOOD, COST_ARROW_STONE,
                        COST_ARROW_BONE, COST_ARROW_OIL, COST_TOWER_UPGRADE_2);
                break;
            case TOWER_ARROW_4:
                dropCollectables(pos, COST_ARROW_WOOD, COST_ARROW_STONE,
                        COST_ARROW_BONE, COST_ARROW_OIL, COST_TOWER_UPGRADE_3);
                break;
            case TOWER_ARROW_5:
                dropCollectables(pos, COST_ARROW_WOOD, COST_ARROW_STONE,
                        COST_ARROW_BONE, COST_ARROW_OIL, COST_TOWER_UPGRADE_4);
                break;
        }
    } else if (towerType == 1) {
        switch (type) {
            case TOWER_CANNON_1:
                dropCollectables(pos, COST_CANNON_WOOD, COST_CANNON_STONE,
                        COST_CANNON_BONE, COST_CANNON_OIL, 0);
                break;
            case TOWER_CANNON_2:
                dropCollectables(pos, COST_CANNON_WOOD, COST_CANNON_STONE,
                        COST_CANNON_BONE, COST_CANNON_OIL, COST_TOWER_UPGRADE);
                break;
            case TOWER_CANNON_3:
                dropCollectables(pos, COST_CANNON_WOOD, COST_CANNON_STONE,
                        COST_CANNON_BONE, COST_CANNON_OIL,COST_TOWER_UPGRADE_2);
                break;
            case TOWER_CANNON_4:
                dropCollectables(pos, COST_CANNON_WOOD, COST_CANNON_STONE,
                        COST_CANNON_BONE, COST_CANNON_OIL,COST_TOWER_UPGRADE_3);
                break;
            case TOWER_CANNON_5:
                dropCollectables(pos, COST_CANNON_WOOD, COST_CANNON_STONE,
                        COST_CANNON_BONE, COST_CANNON_OIL,COST_TOWER_UPGRADE_4);
                break;
        }
    } else if (towerType == 2) {
        switch (type) {
            case TOWER_FLAME_1:
                dropCollectables(pos, COST_FLAME_WOOD, COST_FLAME_STONE,
                        COST_FLAME_BONE, COST_FLAME_OIL, 0);
                break;
            case TOWER_FLAME_2:
                dropCollectables(pos, COST_FLAME_WOOD, COST_FLAME_STONE,
                        COST_FLAME_BONE, COST_FLAME_OIL, COST_TOWER_UPGRADE);
                break;
            case TOWER_FLAME_3:
                dropCollectables(pos, COST_FLAME_WOOD, COST_FLAME_STONE,
                        COST_FLAME_BONE, COST_FLAME_OIL, COST_TOWER_UPGRADE_2);
                break;
            case TOWER_FLAME_4:
                dropCollectables(pos, COST_FLAME_WOOD, COST_FLAME_STONE,
                        COST_FLAME_BONE, COST_FLAME_OIL, COST_TOWER_UPGRADE_3);
                break;
            case TOWER_FLAME_5:
                dropCollectables(pos, COST_FLAME_WOOD, COST_FLAME_STONE,
                        COST_FLAME_BONE, COST_FLAME_OIL, COST_TOWER_UPGRADE_4);
                break;
        }
    } else if (towerType == 3) {
        switch (type) {
            case TOWER_TAR_1:
                dropCollectables(pos, COST_TAR_WOOD, COST_TAR_STONE,
                        COST_TAR_BONE, COST_TAR_OIL, 0);
                break;
            case TOWER_TAR_2:
                dropCollectables(pos, COST_TAR_WOOD, COST_TAR_STONE,
                        COST_TAR_BONE, COST_TAR_OIL, COST_TOWER_UPGRADE);
                break;
            case TOWER_TAR_3:
                dropCollectables(pos, COST_TAR_WOOD, COST_TAR_STONE,
                        COST_TAR_BONE, COST_TAR_OIL, COST_TOWER_UPGRADE_2);
                break;
            case TOWER_TAR_4:
                dropCollectables(pos, COST_TAR_WOOD, COST_TAR_STONE,
                        COST_TAR_BONE, COST_TAR_OIL, COST_TOWER_UPGRADE_3);
                break;
            case TOWER_TAR_5:
                dropCollectables(pos, COST_TAR_WOOD, COST_TAR_STONE,
                        COST_TAR_BONE, COST_TAR_OIL, COST_TOWER_UPGRADE_4);
                break;
        }
    } else if (towerType == 4) {
        switch (type) {
            case TOWER_FLAK_1:
                dropCollectables(pos, COST_FLAK_WOOD, COST_FLAK_STONE,
                        COST_FLAK_BONE, COST_FLAK_OIL, 0);
                break;
            case TOWER_FLAK_2:
                dropCollectables(pos, COST_FLAK_WOOD, COST_FLAK_STONE,
                        COST_FLAK_BONE, COST_FLAK_OIL, COST_TOWER_UPGRADE);
                break;
            case TOWER_FLAK_3:
                dropCollectables(pos, COST_FLAK_WOOD, COST_FLAK_STONE,
                        COST_FLAK_BONE, COST_FLAK_OIL, COST_TOWER_UPGRADE_2);
                break;
            case TOWER_FLAK_4:
                dropCollectables(pos, COST_FLAK_WOOD, COST_FLAK_STONE,
                        COST_FLAK_BONE, COST_FLAK_OIL, COST_TOWER_UPGRADE_3);
                break;
            case TOWER_FLAK_5:
                dropCollectables(pos, COST_FLAK_WOOD, COST_FLAK_STONE,
                        COST_FLAK_BONE, COST_FLAK_OIL, COST_TOWER_UPGRADE_4);
                break;
        }
    }
    destroyObject(currentTile->getExtension());
    currentTile->setExtension(NULL);
    currentTile->setActionType(TILE_BUILDABLE);
}
//TODO macca gem validation
bool Driver::upgradeTower(QPointF pos) {
    Tile* currentTile = gameMap_->getTile(pos.x(), pos.y());
    Tower* t = (Tower*)currentTile->getExtension();
    int level = t->getType() & 0x0F;

    if (level == 1 && gemCount_ >= GEMS_TO_L2) {
        setGemCount(gemCount_ - GEMS_TO_L2);
        switch (t->getType()) {
            case TOWER_ARROW_1:
                t->setType(TOWER_ARROW_2);
                t->setComponents();
                break;
            case TOWER_CANNON_1:
                t->setType(TOWER_CANNON_2);
                t->setComponents();
                break;
            case TOWER_FLAME_1:
                t->setType(TOWER_FLAME_2);
                t->setComponents();
                break;
            case TOWER_TAR_1:
                t->setType(TOWER_TAR_2);
                t->setComponents();
                break;
            case TOWER_FLAK_1:
                t->setType(TOWER_FLAK_2);
                t->setComponents();
                break;
        }
        return true;
    } else if (level == 2 && gemCount_ >= GEMS_TO_L3) {
        setGemCount(gemCount_ - GEMS_TO_L3);
        switch (t->getType()) {
            case TOWER_ARROW_2:
                t->setType(TOWER_ARROW_3);
                t->setComponents();
                break;
            case TOWER_CANNON_2:
                t->setType(TOWER_CANNON_3);
                t->setComponents();
                break;
            case TOWER_FLAME_2:
                t->setType(TOWER_FLAME_3);
                t->setComponents();
                break;
            case TOWER_TAR_2:
                t->setType(TOWER_TAR_3);
                t->setComponents();
                break;
            case TOWER_FLAK_2:
                t->setType(TOWER_FLAK_3);
                t->setComponents();
                break;
        }
        return true;
    } else if (level == 3 && gemCount_ >= GEMS_TO_L4) {
        setGemCount(gemCount_ - GEMS_TO_L4);
        switch (t->getType()) {
            case TOWER_ARROW_3:
                t->setType(TOWER_ARROW_4);
                t->setComponents();
                break;
            case TOWER_CANNON_3:
                t->setType(TOWER_CANNON_4);
                t->setComponents();
                break;
            case TOWER_FLAME_3:
                t->setType(TOWER_FLAME_4);
                t->setComponents();
                break;
            case TOWER_TAR_3:
                t->setType(TOWER_TAR_4);
                t->setComponents();
                break;
            case TOWER_FLAK_3:
                t->setType(TOWER_FLAK_4);
                t->setComponents();
                break;
        }
        return true;
    } else if (level == 4 && gemCount_ >= GEMS_TO_L5) {
        setGemCount(gemCount_ - GEMS_TO_L5);
        switch (t->getType()) {
            case TOWER_ARROW_4:
                t->setType(TOWER_ARROW_5);
                t->setComponents();
                break;
            case TOWER_CANNON_4:
                t->setType(TOWER_CANNON_5);
                t->setComponents();
                break;
            case TOWER_FLAME_4:
                t->setType(TOWER_FLAME_5);
                t->setComponents();
                break;
            case TOWER_TAR_4:
                t->setType(TOWER_TAR_5);
                t->setComponents();
                break;
            case TOWER_FLAK_4:
                t->setType(TOWER_FLAK_5);
                t->setComponents();
                break;
        }
        return true;
    }
    return false;
}

bool Driver::upgradePlayer(int id, int type, int* cost) {
    if ((gemCount_ < GEMS_SPEED && type == UPGRADE_SPEED) 
            || (gemCount_ < GEMS_HARVEST && type == UPGRADE_HARVEST)
            || (gemCount_ < GEMS_RECOVERY && type == UPGRADE_RECOVERY)) {
        return false;
    }

#ifdef SERVER
    if (type == UPGRADE_SPEED) {
        setGemCount(gemCount_ - GEMS_SPEED);
        if (cost != NULL) {
            *cost = GEMS_SPEED;
        }
    } else if (type == UPGRADE_HARVEST) {
        setGemCount(gemCount_ - UPGRADE_HARVEST);
        if (cost != NULL) {
            *cost = GEMS_HARVEST;
        }
    } else {
        setGemCount(gemCount_ - UPGRADE_RECOVERY);
        if (cost != NULL) {
            *cost = GEMS_RECOVERY;
        }
    }
    return true;
#endif

    Player* player = (Player*)mgr_->findObject(id);

    switch (type) {
    case UPGRADE_SPEED:
        setGemCount(gemCount_ - GEMS_SPEED);
        if (player->hasEffect(EFFECT_SLOW)) {
            player->deleteEffect(EFFECT_SLOW);
            ((PlayerPhysicsComponent*)player->getPhysicsComponent())
                ->setMaxVelocity(PLAYER_UPGRADE_V);
            player->createEffect(EFFECT_SLOW);
        } else if (player->hasEffect(EFFECT_FAST)) {
            player->deleteEffect(EFFECT_FAST);
            ((PlayerPhysicsComponent*)player->getPhysicsComponent())
                ->setMaxVelocity(PLAYER_UPGRADE_V);
            player->createEffect(EFFECT_FAST);
        }
        break;
    case UPGRADE_HARVEST:
        setGemCount(gemCount_ - GEMS_HARVEST);
        player->setHarvestTime(HARVEST_COUNTDOWN_UPGRADE);
        break;
    case UPGRADE_RECOVERY:
        setGemCount(gemCount_ - GEMS_RECOVERY);
        player->setStunUpgrade(true);
        break;
    }
    return true;
}

QVector2D Driver::getRandomVector() {
    float d = ((rand() % 1000) / 21.0) + 50;
    float x = (rand() % 1000) - 500;
    float y = (rand() % 1000) - 500;

    QVector2D v = QVector2D(x, y);
    v.normalize();

    return (v * d);
}

void Driver::dropCollectables(QPointF pos,
        int wood, int stone, int bone, int oil, int gem) {
    int i = 0;
    // TODO reduce the number of dropped items here

    for (i = 0; i < wood; i++) {
        requestCollectable(RESOURCE_WOOD, pos, getRandomVector());
    }
    for (i = 0; i < stone; i++) {
        requestCollectable(RESOURCE_STONE, pos, getRandomVector());
    }
    for (i = 0; i < bone; i++) {
        requestCollectable(RESOURCE_BONE, pos, getRandomVector());
    }
    for (i = 0; i < oil; i++) {
        requestCollectable(RESOURCE_TAR, pos, getRandomVector());
    }
    for (i = 0; i < gem; i++) {
        requestCollectable(RESOURCE_GEM, pos, getRandomVector());
    }
}

} /* end namespace td */

