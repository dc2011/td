#include "ProjectileGraphicsComponentTypes.h"

namespace td {

/* Initialize the QPixmap arrays for all classes */
QPixmap* ArrowProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* ArrowProjectileL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* ArrowProjectileL3GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonProjectileL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* CannonProjectileL3GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarProjectileL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* TarProjectileL3GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FireProjectileL1GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FireProjectileL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FireProjectileL3GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakProjectileGraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakProjectileL2GraphicsComponent::pixmapImgs_ = NULL;
QPixmap* FlakProjectileL3GraphicsComponent::pixmapImgs_ = NULL;

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
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_ARROW;
    pixmapIndex_ = 0;
}

ArrowProjectileL2GraphicsComponent::ArrowProjectileL2GraphicsComponent() 
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void ArrowProjectileL2GraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_ARROW_2_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_ARROW_2;
    pixmapIndex_ = 0;
}

ArrowProjectileL3GraphicsComponent::ArrowProjectileL3GraphicsComponent() 
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void ArrowProjectileL3GraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_ARROW_3_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_ARROW_3;
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
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_CANNON;
    pixmapIndex_ = 0;
}

CannonProjectileL2GraphicsComponent::CannonProjectileL2GraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void CannonProjectileL2GraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_CANNON_2_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_CANNON_2;
    pixmapIndex_ = 0;
}

CannonProjectileL3GraphicsComponent::CannonProjectileL3GraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void CannonProjectileL3GraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_CANNON_3_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_CANNON_3;
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
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_TAR;
    pixmapIndex_ = 0;
}

TarProjectileL2GraphicsComponent::TarProjectileL2GraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void TarProjectileL2GraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_TAR_2_MAX];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_TAR_2;
    pixmapIndex_ = 0;
}

TarProjectileL3GraphicsComponent::TarProjectileL3GraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void TarProjectileL3GraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_TAR_3_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_TAR_3;
    pixmapIndex_ = 0;
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

FireProjectileL1GraphicsComponent::FireProjectileL1GraphicsComponent()
        : FireProjectileGraphicsComponent() {
    emit created(this);
}

void FireProjectileL1GraphicsComponent::initPixmaps() {
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
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_4;
    pixmapIndex_ = 0;
    timerID_ = this->startTimer(125);
}

FireProjectileL2GraphicsComponent::FireProjectileL2GraphicsComponent()
        : FireProjectileGraphicsComponent() {
    emit created(this);
}

void FireProjectileL2GraphicsComponent::initPixmaps() {
    animateMod_ = PIX_PROJ_FIRE_2_MAX;
    arrayIndexMin_ = pixmapIndex_ = 0;
    arrayIndexMax_ = PIX_PROJ_FIRE_2_MAX - 1;
    currentIndex_ = 0;
    if (pixmapImgs_) {
        timerID_ = this->startTimer(125);
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_FIRE_2_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_2_0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_2_1;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_2_2;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_2_3;
    pixmapIndex_ = 0;
    timerID_ = this->startTimer(125);
}

FireProjectileL3GraphicsComponent::FireProjectileL3GraphicsComponent()
        : FireProjectileGraphicsComponent() {
    emit created(this);
}

void FireProjectileL3GraphicsComponent::initPixmaps() {
    animateMod_ = PIX_PROJ_FIRE_3_MAX;
    arrayIndexMin_ = pixmapIndex_ = 0;
    arrayIndexMax_ = PIX_PROJ_FIRE_3_MAX - 1;
    currentIndex_ = 0;
    if (pixmapImgs_) {
        timerID_ = this->startTimer(125);
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_FIRE_3_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_3_0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_3_1;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_3_2;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_3_3;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FIRE_3_4;
    pixmapIndex_ = 0;
    timerID_ = this->startTimer(125);
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
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FLAK;
    pixmapIndex_ = 0;
}

FlakProjectileL2GraphicsComponent::FlakProjectileL2GraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void FlakProjectileL2GraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_FLAK_2_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FLAK_2;
    pixmapIndex_ = 0;
}

FlakProjectileL3GraphicsComponent::FlakProjectileL3GraphicsComponent()
        : ProjectileGraphicsComponent() {
    emit created(this);
}

void FlakProjectileL3GraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PROJ_FLAK_3_MAX];
    }
    //TODO: add animation images here

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PROJ_FLAK_3;
    pixmapIndex_ = 0;
}

} /* end namespace td */

