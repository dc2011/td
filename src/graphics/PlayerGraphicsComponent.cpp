#include "PlayerGraphicsComponent.h"
#include "../engine/Player.h"

namespace td {

PlayerGraphicsComponent::PlayerGraphicsComponent()
        : GraphicsComponent()
{
    animateMod = 4;
    animateCount = 0;
    animateConnect();
    emit created(this);
    /* Do init-type stuff here */
}

//PlayerGraphicsComponent::~PlayerGraphicsComponent() {
//}

void PlayerGraphicsComponent::update(GameObject* obj) {
    Player* player = (Player*)obj;
    if (!player->isDirty()) {//checks if object is dirty.
        return;
    }
    player->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = player->getPos();
    dp->moving  = player->getVelocity().length() != 0;
    //dp->scale   = player->getScale();  will likely be a constant value here
    dp->degrees = player->getOrientation();
    emit signalDraw(dp, this);
}

void PlayerGraphicsComponent::initPixmaps() {
    //TODO: add animation logic here?
    pixmapImgs_ = new QPixmap[PIX_PLAYER_MAX];
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_0;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_1;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_2;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_3;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_4;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_5;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_6;
    pixmapIndex_ = 0;
}

void PlayerGraphicsComponent::animate() {
    
    int pos;
    
    if (!isMoving_) {
        pixmapIndex_ = 0;
        setImgIndex(pixmapIndex_);
        return;
    }

    if (pixmapIndex_ == 0) {
	pos = rand() % 2 + 1;
        pos == 1 ? pixmapIndex_ = 0 : pixmapIndex_ = 3;
    }
    
    if (!(animateCount++ % animateMod)) {
        ++pixmapIndex_ >= PIX_PLAYER_MAX ? pixmapIndex_ = 1 : pixmapIndex_;
        setImgIndex(pixmapIndex_);
    }
}

} /* end namespace td */
