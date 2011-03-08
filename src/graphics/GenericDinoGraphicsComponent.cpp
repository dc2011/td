#include "GenericDinoGraphicsComponent.h"
#include "../engine/Unit.h"

GenericDinoGraphicsComponent::GenericDinoGraphicsComponent()
        : NPCGraphicsComponent() {
    animateMod = 7;
    animateCount = 0;
    animateConnect();
    emit created(this);
}

GenericDinoGraphicsComponent::~GenericDinoGraphicsComponent() {}

void GenericDinoGraphicsComponent::initPixmaps() {
    //TODO: add animation images here
    pixmapImgs = new QPixmap[PIX_GENERICDINO_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex++] = PIX_GENERICDINO_0;
    pixmapImgs[pixmapIndex++] = PIX_GENERICDINO_1;
    pixmapIndex = 0; //sets image back to start
}

void GenericDinoGraphicsComponent::animate() {
    if (!(animateCount++ % animateMod)) {
        pixmapIndex = (pixmapIndex)? 0 : 1;
        setImgIndex(pixmapIndex);
    }
}
