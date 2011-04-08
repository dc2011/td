#include "PlayerGraphicsComponent.h"
#include "../engine/Player.h"
#include "../engine/CDriver.h"

namespace td {

QPixmap * PlayerGraphicsComponent::pixmapImgs_ = 0;

PlayerGraphicsComponent::PlayerGraphicsComponent(QString nickname)
        : GraphicsComponent(), nickname_(nickname),
          showName_(false), nameShowing_(false)
{
    animateMod_ = 4;
    animateCount_ = 0; 
    resourceProgressBar_ = new QGraphicsRectItem(QRectF(OFFSCREEN,OFFSCREEN,
                                                    RESBAR_WIDTH, RESBAR_HEIGHT));
    resourceProgressBar_->setBrush(QBrush(Qt::blue));
    CDriver::instance()->getMainWindow()->getScene()->addItem(resourceProgressBar_);
    emit created(this);
}

void PlayerGraphicsComponent::update(GameObject* obj) {
    Player* player = (Player*)obj;

    if (player->getHarvestCountdown() != HARVEST_COUNTDOWN) {
        resourceProgressShowing_ = true;
        resourceProgress_ = (double) player->getHarvestCountdown()
                            / HARVEST_COUNTDOWN;
    }

    if (!player->isDirty() && pixmapIndex_ == 0 && !resourceProgressShowing_) {
        //checks if object is dirty or in mid-animation, or if the resource progress
        //bar is being updated
        return;
    }

    if (player->getHarvestCountdown() == HARVEST_COUNTDOWN) {
        resourceProgressShowing_ = false;
    }

    player->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = player->getPos();
    dp->moving  = player->getVelocity().length() != 0;
    //dp->scale   = player->getScale();  will likely be a constant value here
    dp->degrees = player->getOrientation();
    emit signalDraw(dp, this, LAYER_PLAYER);
}

void PlayerGraphicsComponent::draw(DrawParams* dp, int layer) {
    
    if (resourceProgressShowing_) {
        resourceProgressBar_->setVisible(true);
        resourceProgressBar_->setRect(0, 0,
                                  RESBAR_WIDTH * resourceProgress_, RESBAR_HEIGHT);
        resourceProgressBar_->setPos((dp->pos.x()
                    - resourceProgressBar_->boundingRect().center().x()),
                    (dp->pos.y()
                    - (getPixmapItem()->boundingRect().height())/2));
        resourceProgressBar_->setZValue(layer);
        resourceProgressBar_->update();
    } else {
        resourceProgressBar_->setVisible(false);
    }

    if (showName_) {
        label_->setPos(dp->pos.x() - label_->boundingRect().center().x(),
                       dp->pos.y() - getPixmapItem()->boundingRect().height());
        label_->setZValue(layer);
        label_->setVisible(true);
        label_->update();
        nameShowing_ = true;
    } else {
        if (nameShowing_) {
            label_->setVisible(false);
            label_->update();
            nameShowing_ = false;
        }
    }

    GraphicsComponent::draw(dp, layer);
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
    
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ >= PIX_PLAYER_MAX ? pixmapIndex_ = 1 : pixmapIndex_;
        setImgIndex(pixmapIndex_);
    }
}

void PlayerGraphicsComponent::initPixmaps() {
    label_ = new QGraphicsTextItem(nickname_);

    label_->setDefaultTextColor (QColor(0,255,0));
    CDriver::instance()->getMainWindow()->getScene()->addItem(label_);
    label_->setVisible(false);

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

} /* end namespace td */
