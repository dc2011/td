#include "GenericDinoGraphicsComponent.h"
#include "../engine/Unit.h"

namespace td {

GenericDinoGraphicsComponent::GenericDinoGraphicsComponent()
        : NPCGraphicsComponent() {
    animateMod_ = 7;
    animateCount_ = 0;
    animateConnect();
    emit created(this);
}

GenericDinoGraphicsComponent::~GenericDinoGraphicsComponent() {}

void GenericDinoGraphicsComponent::initPixmaps() {
    //TODO: add animation images here
    pixmapImgs_ = new QPixmap[PIX_GENERICDINO_MAX];
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_GENERICDINO_0;
    pixmapImgs_[pixmapIndex_++] = PIX_GENERICDINO_1;
    pixmapIndex_ = 0; //sets image back to start
}

void GenericDinoGraphicsComponent::animate() {
    if (!(animateCount_++ % animateMod_)) {
        pixmapIndex_ = (pixmapIndex_)? 0 : 1;
        setImgIndex(pixmapIndex_);
    }
}

} /* end namespace td */
