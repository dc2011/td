#include "GenericDinoGraphicsComponent.h"
#include "../engine/Unit.h"

namespace td {

GenericDinoGraphicsComponent::GenericDinoGraphicsComponent()
        : GraphicsComponent() {
    animateMod = 7;
    animateCount = 0;
    animateConnect();
    emit created(this);
}

GenericDinoGraphicsComponent::~GenericDinoGraphicsComponent() {}

void GenericDinoGraphicsComponent::update(GameObject* obj) {
    Unit* gdgc = (Unit*)obj;
    if (!gdgc->isDirty()) {//checks if object is dirty.
        return;
    }
    gdgc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = gdgc->getPos();
    dp->moving  = 1;
    //player->getVelocity().length() != 0;
    //dp->scale   = tower->getScale();
    dp->degrees = gdgc->getOrientation();
    emit signalDraw(dp, this);
}

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

} /* end namespace td */
