#include "CollectableGraphicsComponentTypes.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* ResourceCollectableGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* GemCollectableGraphicsComponent::pixmapImgs_ = NULL;

ResourceCollectableGraphicsComponent::ResourceCollectableGraphicsComponent() 
        : CollectableGraphicsComponent() {
    emit created(this);
}

void ResourceCollectableGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_COLL_RESOURCE_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_COLL_RESOURCE;
    pixmapIndex_ = 0;
}

GemCollectableGraphicsComponent::GemCollectableGraphicsComponent()
        : CollectableGraphicsComponent() {
    emit created(this);
}

void GemCollectableGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_COLL_GEM_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_COLL_GEM;
    pixmapIndex_ = 0;
}

} /* end namespace td */

