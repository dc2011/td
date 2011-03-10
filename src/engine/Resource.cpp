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
        case RESOURCE_LUMBER:   pixmapPath = PIX_RESOURCE_LUMBER;   break;
        case RESOURCE_CRYSTAL:  pixmapPath = PIX_RESOURCE_CRYSTAL;  break;
        case RESOURCE_OIL:      pixmapPath = PIX_RESOURCE_OIL;      break;
        case RESOURCE_TAR:      pixmapPath = PIX_RESOURCE_TAR;      break;
        case RESOURCE_STONE:    pixmapPath = PIX_RESOURCE_STONE;    break;
        case RESOURCE_IRON:     pixmapPath = PIX_RESOURCE_IRON;     break;
    }
    GraphicsComponent* graphics = new ResourceGraphicsComponent(pixmapPath);

    this->setGraphicsComponent(graphics);
}

} // end of namespace td

