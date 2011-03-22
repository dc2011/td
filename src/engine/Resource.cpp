#include "Resource.h"
#include "CDriver.h"
#include "Effect.h"
#include "../graphics/ResourceGraphicsComponent.h"
#include "../util/defines.h"

namespace td {

void Resource::update() {
    graphics_->update(this);
    //physics_->update(this);

#ifndef SERVER
    //CDriver::updateServer(this);
#endif
}

void Resource::initComponents() {
    componentsInitialized_ = false;
}

void Resource::initComponents(int resourceType) {
#ifndef SERVER
    GraphicsComponent* graphics = new ResourceGraphicsComponent(resourceType);
    this->setGraphicsComponent(graphics);
#endif
}

} // end of namespace td

