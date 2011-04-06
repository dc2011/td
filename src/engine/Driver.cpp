#include "Driver.h"
#include "Tower.h"
#include "NPC.h"
#include "Resource.h"

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

Tower* Driver::createTower(int type) {
    Tower* tower = (Tower*)mgr_->createObject(Tower::clsIdx());

    tower->setType(type);
    tower->initComponents();

    connect(gameTimer_, SIGNAL(timeout()), tower, SLOT(update()));

    return tower;
}

NPC* Driver::createNPC(int type) {
    NPC* npc = (NPC*)mgr_->createObject(NPC::clsIdx());

    npc->setType(type);
    npc->initComponents();

    connect(gameTimer_, SIGNAL(timeout()), npc, SLOT(update()));

    return npc;
}

/*Resource* Driver::createResource(int type) {
}*/

} /* end namespace td */
