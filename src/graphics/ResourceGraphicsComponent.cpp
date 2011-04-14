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
    DrawParams* dp = new DrawParams();
    dp->pos     = resource->getPos();
    //dp->moving  = 1;
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
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_WOOD;
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_STONE;
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_BONE;
    pixmapImgs_[pixmapIndex_++] = PIX_RESOURCE_TAR;
    setIndexValue();
}

void ResourceGraphicsComponent::setIndexValue() {
    switch (resourceType_) {
        case RESOURCE_WOOD:     pixmapIndex_ = 0;   break;
        case RESOURCE_STONE:    pixmapIndex_ = 1;   break;
        case RESOURCE_BONE:     pixmapIndex_ = 2;   break;
        case RESOURCE_TAR:      pixmapIndex_ = 3;   break;
    }
}

QPixmap * ResourceGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

} /* end namespace td */
