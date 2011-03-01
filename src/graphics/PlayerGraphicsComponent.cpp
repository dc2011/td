#include "PlayerGraphicsComponent.h"
#include "../engine/Player.h"

PlayerGraphicsComponent::PlayerGraphicsComponent()
        : GraphicsComponent()
{
    animateMod = 5;
    animateCount = 0;
    animateConnect();
    emit created(this);
    /* Do init-type stuff here */
}

//PlayerGraphicsComponent::~PlayerGraphicsComponent() {
//}

void PlayerGraphicsComponent::update(GameObject* obj) {
    Player* player = (Player*)obj;
    if (!player->getDirtyStatus()) {//checks if object is dirty.
        return;
    }
    player->setToClean();
    DrawParams* dp = new DrawParams();
    dp->pos     = player->getPos();
    dp->moving  = player->getVelocity().length() != 0;
    //dp->scale   = player->getScale();  will likely be a constant value here
    dp->degrees = player->getOrientation();
    emit signalDraw(dp, this);
}

void PlayerGraphicsComponent::initPixmaps() {
    //TODO: add animation logic here?
    pixmapImgs = new QPixmap[PIX_PLAYER_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex++] = PIX_PLAYER_0;
    pixmapImgs[pixmapIndex++] = PIX_PLAYER_1;
    pixmapImgs[pixmapIndex++] = PIX_PLAYER_2;
    pixmapImgs[pixmapIndex++] = PIX_PLAYER_3;
    pixmapImgs[pixmapIndex++] = PIX_PLAYER_4;
    pixmapImgs[pixmapIndex++] = PIX_PLAYER_5;
    pixmapIndex = 0;
}

void PlayerGraphicsComponent::animate() {
    if (!(animateCount++ % animateMod)) {
        pixmapIndex = (pixmapIndex != PIX_PLAYER_MAX - 1)? pixmapIndex + 1 : 0;
        setImgIndex(pixmapIndex);
    }
}

