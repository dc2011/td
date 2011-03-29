#include "Resource.h"
#include "CDriver.h"
#include "Effect.h"
#include "../graphics/ResourceGraphicsComponent.h"
#include "../util/defines.h"

namespace td {

void Resource::update() {
    if (isDirty()) {
        //getDriver()->update(this);
    }

    graphics_->update(this);
    //physics_->update(this);
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

