#include "Resource.h"
#include "CDriver.h"
#include "Effect.h"
#include "../graphics/ResourceGraphicsComponent.h"
#include "../util/defines.h"

namespace td {

void Resource::update() {
    graphics_->update(this);
    //physics_->update(this);
    CDriver::updateServer(this);
}

void Resource::initComponents() {
    componentsInitialized_ = false;
}

void Resource::initComponents(int resourceType) {
    QString pixmapPath;

    switch (resourceType) {
        case RESOURCE_LUMBER: pixmapPath = PIX_RESOURCE_LUMBER;   break;
        //case TOWER_CANNON:  pixmapPath = PIX_TOWER_CANNON;  break;
        //case TOWER_TAR:     pixmapPath = PIX_TOWER_TAR;     break;
        //case TOWER_FLAME:   pixmapPath = PIX_TOWER_FLAME;   break;
        //case TOWER_FLAK:    pixmapPath = PIX_TOWER_FLAK;    break;
    }
    GraphicsComponent* graphics = new ResourceGraphicsComponent(pixmapPath);

    this->setGraphicsComponent(graphics);
}

} // end of namespace td

