#include "Collectable.h"

#include "../graphics/ArrowTowerGraphicsComponent"

namespace td {

Collectable::Collectable(QObject* parent) 
        : Collectable(parent) 
    //TODO init physics info
    //QVector2D force(0, 0);
    //this->setForce(force);

    //this->setPos(100, 100);
}

void Collectable::networkRead(Stream* s) {
    GameUnit::networkRead(s);
}

void Collectable::networkWrite(Stream* s) {
    GameUnit::networkWrite(s);
}

void Collectable::initComponents() {
#ifndef SERVER
    /* Client-side has a Graphics Component */
    // TODO
    graphics_ = new ArrowTowerGraphicsComponent();
    //graphics_->update(this);
#endif
}

void Collectable::update() {
    if (input_ != NULL) {
        input_->update(this);
    }
    if (physics_ != NULL) {
        physics_->update(this);
    }
    if (graphics_ != NULL) {
        graphics_->update(this);
    }
    if (harvesting_ != RESOURCE_NONE) {
        harvestResource();
    }
}

} // end namespace td

