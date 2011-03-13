#include "ResourceGraphicsComponent.h"
#include "../engine/Resource.h"
#include "../util/defines.h"

namespace td {

QPixmap * ResourceGraphicsComponent::pixmapImgs_ = 0;

ResourceGraphicsComponent::ResourceGraphicsComponent(int resourceType)
        : GraphicsComponent(), resourceType_(resourceType) {
    emit created(this);
}

ResourceGraphicsComponent::~ResourceGraphicsComponent() {}

void ResourceGraphicsComponent::update(GameObject* obj) {
    Resource* resource = (Resource*)obj;
    //if (!resource->getDirtyStatus()) {//checks if object is dirty.
    //    return;
    //}
    //resource->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = resource->getPos();
    dp->moving  = 1;
    //player->getVelocity().length() != 0;
    dp->scale   = 1;//resource->getScale();
    dp->degrees = resource->getOrientation();
    emit signalDraw(dp, this, LAYER_DEFAULT);
}

void ResourceGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        setIndexValue();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_RESOURCE_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_LUMBER;
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_CRYSTAL;
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_OIL;
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_TAR;
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_STONE;
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_IRON;
    setIndexValue();
}

void ResourceGraphicsComponent::setIndexValue() {
    switch (resourceType_) {
        case RESOURCE_LUMBER:   pixmapIndex_ = 0;   break;
        case RESOURCE_CRYSTAL:  pixmapIndex_ = 1;   break;
        case RESOURCE_OIL:      pixmapIndex_ = 2;   break;
        case RESOURCE_TAR:      pixmapIndex_ = 3;   break;
        case RESOURCE_STONE:    pixmapIndex_ = 4;   break;
        case RESOURCE_IRON:     pixmapIndex_ = 5;   break;
    }
}

QPixmap * ResourceGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

} /* end namespace td */
