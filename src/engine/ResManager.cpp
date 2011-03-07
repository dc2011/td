#include "ResManager.h"
#include "Player.h"
#include "Projectile.h"
#include "NPC.h"
#include "Tower.h"

namespace td {

ResManager::ResManager() {
    objects_ = QVector<QList<GameObject*> >(clsidx::kMAX_CLASS_INDEX);
}

ResManager::~ResManager() {
    objects_.clear();
}

GameObject* ResManager::internalCreateObject(unsigned char type) {
    GameObject* ret = NULL;
    unsigned int id = 0;

    switch (type) {
        case clsidx::kPlayer:
            ret = new Player();
            id = (Player::clsIdx() << 24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kProjectile:
            ret = new Projectile();
            id = (Projectile::clsIdx() << 24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kNPC:
            ret = new NPC();
            id = (NPC::clsIdx() << 24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kTower:
	    ret = new Tower();
	    id = (Tower::clsIdx() <<24) | objects_[type].size();
	    ret->setID(id);
	    break;
        case clsidx::kGameObject:
        case clsidx::kUnit:
        default:
            break;
    }

    return ret;
}

GameObject* ResManager::createObject(unsigned char type) {
    GameObject* ret = internalCreateObject(type);

    if (ret == NULL) {
        return NULL;
    }

    objects_[type].append(ret);

    return ret;
}

GameObject* ResManager::createObjectWithID(unsigned int id) {
    GameObject* ret = internalCreateObject((id & 0xFF000000) >> 24);

    if (ret == NULL) {
        return NULL;
    }

    ret->setID(id);

    addExistingObject(ret);

    return ret;
}

void ResManager::addExistingObject(GameObject* obj)
{
    unsigned char type = (obj->getID() & 0xFF000000) >> 24;
    int id = obj->getID() & 0x00FFFFFF;

    while (id >= objects_[type].size()) {
        objects_[type].append(NULL);
    }

    objects_[type][id] = obj;
}

GameObject* ResManager::findObject(unsigned int id) {
    unsigned char type = (id & 0xFF000000) >> 24;
    int objid = (id & 0x00FFFFFF);

    if (type >= clsidx::kMAX_CLASS_INDEX
            || objid >= objects_[type].size())
    {
        return NULL;
    }

    return objects_[type][objid];
}

void ResManager::deleteObject(unsigned int id) {
    unsigned char type = (id & 0xFF000000) >> 24;
    unsigned int objid = (id & 0x00FFFFFF);

    GameObject* obj = findObject(id);

    if (obj != NULL) {
        objects_[type].removeAt(objid);
        delete obj;
        obj = NULL;
    }
}

void ResManager::deleteObject(GameObject* obj) {
    deleteObject(obj->getID());

    obj = NULL;
}

unsigned int ResManager::countObjects() const {
    unsigned int count = 0;

    for (int i = 0; i < clsidx::kMAX_CLASS_INDEX; i++) {
        count += objects_[i].size();
    }

    return count;
}

} /* end namespace td */
