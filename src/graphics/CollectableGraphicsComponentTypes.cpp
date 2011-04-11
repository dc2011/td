#include "CollectableGraphicsComponentTypes.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* WoodCollectableGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* StoneCollectableGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* BoneCollectableGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarCollectableGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* GemCollectableGraphicsComponent::pixmapImgs_ = NULL;

WoodCollectableGraphicsComponent::WoodCollectableGraphicsComponent() 
        : CollectableGraphicsComponent() {
    emit created(this);
}

void WoodCollectableGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_COLL_WOOD_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_COLL_WOOD;
    pixmapIndex_ = 0;
}

StoneCollectableGraphicsComponent::StoneCollectableGraphicsComponent() 
        : CollectableGraphicsComponent() {
    emit created(this);
}

void StoneCollectableGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_COLL_STONE_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_COLL_STONE;
    pixmapIndex_ = 0;
}

BoneCollectableGraphicsComponent::BoneCollectableGraphicsComponent() 
        : CollectableGraphicsComponent() {
    emit created(this);
}

void BoneCollectableGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_COLL_BONE_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_COLL_BONE;
    pixmapIndex_ = 0;
}

TarCollectableGraphicsComponent::TarCollectableGraphicsComponent() 
        : CollectableGraphicsComponent() {
    emit created(this);
}

void TarCollectableGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_COLL_TAR_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_COLL_TAR;
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

