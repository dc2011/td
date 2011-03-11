#include "PlayerGraphicsComponent.h"
#include "../engine/Player.h"
#include "../engine/CDriver.h"

namespace td {

    QPixmap * PlayerGraphicsComponent::pixmapImgs_ = 0;

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
    emit signalDraw(dp, this, LAYER_PLAYER);
}

void PlayerGraphicsComponent::initPixmaps() {
    label_ = new QGraphicsTextItem(QString("Warren Master Of The Universe"));

    label_->setDefaultTextColor (QColor(0,255,0));
    CDriver::instance()->getMainWindow()->scene_->addItem(label_);

    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PLAYER_MAX];
    }
    //TODO: add animation logic here?

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

void PlayerGraphicsComponent::draw(DrawParams* dp, int layer) {
    QPointF center = getPixmapItem()->boundingRect().center();

    getPixmapItem()->resetMatrix();//important
    //getPixmapItem()->translate(center.x(), center.y());
    getPixmapItem()->setTransformOriginPoint(center);
    getPixmapItem()->setScale(dp->scale);
    getPixmapItem()->rotate(dp->degrees * -1);

    getPixmapItem()->translate(-center.x(), -center.y());
    //getPixmapItem()->setTransformOriginPoint(-center.x(), -center.y());
    getPixmapItem()->setPos(dp->pos);
    getPixmapItem()->setZValue(layer);
    isMoving_ = dp->moving;

    center = label_->boundingRect().center();
    //dp->pos.setX(dp->pos + (int)center.x);
    label_->setPos(dp->pos.x() - label_->boundingRect().center().x(),
                   dp->pos.y() - getPixmapItem()->boundingRect().height());
    label_->setZValue(layer);
    label_->update();

    delete dp;

    getPixmapItem()->update();
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

QPixmap * PlayerGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

} /* end namespace td */
