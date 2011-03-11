#include "ResourceGraphicsComponent.h"
#include "../engine/Resource.h"

namespace td {

    QPixmap * ResourceGraphicsComponent::pixmapImgs_ = 0;

ResourceGraphicsComponent::ResourceGraphicsComponent(QString pixmapPath)
        : GraphicsComponent(), pixmapPath_(pixmapPath) {
    emit created(this);
    /* Do init-type stuff here */
}

ResourceGraphicsComponent::~ResourceGraphicsComponent() {}

void ResourceGraphicsComponent::update(GameObject* obj) {
    Resource* resource = (Resource*)obj;
    //if (!tower->getDirtyStatus()) {//checks if object is dirty.
    //    return;
    //}
    resource->resetDirty();

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
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_RESOURCE_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = pixmapPath_;
    pixmapIndex_ = 0; //sets image back to start
}

QPixmap * ResourceGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

} /* end namespace td */
