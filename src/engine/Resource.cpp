#include "Resource.h"
#include "CDriver.h"
#include "Effect.h"
#include "../graphics/ResourceGraphicsComponent.h"
#include "../util/defines.h"

namespace td {

Resource::Resource(QObject* parent) : TileExtension(parent) { }

void Resource::update() {
    if (isDirty()) {
        getDriver()->update(this);
    }

    if (graphics_ != NULL) {
        graphics_->update(this);
    }
}

void Resource::networkRead(Stream* s) {
    TileExtension::networkRead(s);
    
    if (dirty_ & kType) {
        type_ = s->readInt();
    }
    if (dirty_ & kRemaining) {
        remaining_ = s->readInt();
    }
}

void Resource::networkWrite(Stream* s) {
    TileExtension::networkWrite(s);

    if (dirty_ & kType) {
        s->writeInt(type_);
    }
    if (dirty_ & kRemaining) {
        s->writeInt(remaining_);
    }
}

void Resource::initComponents() {
#ifndef SERVER
    switch (type_) {
        case RESOURCE_WOOD:
            setGraphicsComponent(new ResourceGraphicsComponent(RESOURCE_WOOD));
            break;
        case RESOURCE_STONE:
            setGraphicsComponent(new ResourceGraphicsComponent(RESOURCE_STONE));
            break;
        case RESOURCE_BONE:
            setGraphicsComponent(new ResourceGraphicsComponent(RESOURCE_BONE));
            break;
        case RESOURCE_TAR:
            setGraphicsComponent(new ResourceGraphicsComponent(RESOURCE_TAR));
            break;
    }
#endif
}

} // end of namespace td

