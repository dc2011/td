#include "ProjectileGraphicsComponentTypes.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* ArrowProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FireProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakProjectileGraphicsComponent::pixmapImgs_ = NULL;

ArrowProjectileGraphicsComponent::ArrowProjectileGraphicsComponent() 
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void ArrowProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_ARROW_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_ARROW;
    pixmapIndex_ = 0;
}

CannonProjectileGraphicsComponent::CannonProjectileGraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void CannonProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_CANNON_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_CANNON;
    pixmapIndex_ = 0;
}

TarProjectileGraphicsComponent::TarProjectileGraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void TarProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_TAR_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_TAR;
    pixmapIndex_ = 0;
}

FireProjectileGraphicsComponent::FireProjectileGraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void FireProjectileGraphicsComponent::initPixmaps() {
    animateMod_ = PIX_PROJ_FIRE_MAX;
    arrayIndexMin_ = pixmapIndex_ = 0;
    arrayIndexMax_ = PIX_PROJ_FIRE_MAX - 1;
    currentIndex_ = 0;
    if (pixmapImgs_) {
        timerID_ = this->startTimer(125);
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_FIRE_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_1;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_2;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_3;
    pixmapIndex_ = 0;
    timerID_ = this->startTimer(125);
}

void FireProjectileGraphicsComponent::animate() {
    if (animateMod_ == 0) {
        return;
    }

    if (currentIndex_ == 0) {
        currentIndex_ = 1;
        return;
    } else if (currentIndex_ == 1) {
        setImgIndex(currentIndex_);
        currentIndex_ = 2;
        return;
    } else {
        if (currentIndex_ == 2) {
            setImgIndex(currentIndex_);
            currentIndex_ = 3;
            return;
        } else if (currentIndex_ == 3) {
            setImgIndex(currentIndex_);
            currentIndex_ = 2;
            return;
        }
    }

}

void FireProjectileGraphicsComponent::timerEvent(QTimerEvent *) {
    DrawParams* dp = new DrawParams();
    dp->pos = pos_;
    dp->scale = scale_;
    dp->degrees = degrees_;
    this->draw(dp, LAYER_FLYNPC);
}


FlakProjectileGraphicsComponent::FlakProjectileGraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void FlakProjectileGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_FLAK_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FLAK;
    pixmapIndex_ = 0;
}

} /* end namespace td */

