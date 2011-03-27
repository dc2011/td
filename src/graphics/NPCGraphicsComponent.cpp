#include "NPCGraphicsComponent.h"
#include "../engine/NPC.h"
#include "../engine/CDriver.h"

namespace td {

QPixmap * NPCGraphicsComponent::pixmapImgs_ = 0;
bool NPCGraphicsComponent::showHealth_    = 0;

NPCGraphicsComponent::NPCGraphicsComponent()
        : GraphicsComponent() {
    emit created(this);
}

/*
NPCGraphicsComponent::NPCGraphicsComponent(int npcType)
    : GraphicsComponent(), npcType_(npcType) {
    connect(CDriver::instance()->getMainWindow(),  SIGNAL(signalAltHeld(bool)),
            this, SLOT(showHealth(bool)));
    emit created(this);
}
*/

NPCGraphicsComponent::~NPCGraphicsComponent() {
    disconnect(this);
}

void NPCGraphicsComponent::draw(DrawParams* dp, int layer) {

    if (showHealth_) {
        healthbarItem_->setVisible(true);
    healthbarItem_->setRect(QRectF(0, 0, (96*npcHealth), 7));
        if(npcHealth > 0.25 && npcHealth < 0.51) {
            healthbarItem_->setBrush(QBrush(Qt::yellow));
        } else if (npcHealth <= 0.25) {
            healthbarItem_->setBrush(QBrush(Qt::red));
        } else {
            healthbarItem_->setBrush(QBrush(Qt::green));
        }
    healthbarItem_->setPos((dp->pos.x() - healthbarItem_->boundingRect().center().x()),
                   (dp->pos.y() - (getPixmapItem()->boundingRect().height())/2));
    healthbarItem_->setZValue(layer);
    healthbarItem_->update();
    } else {
        healthbarItem_->setVisible(false);
        healthbarItem_->update();
    }

    GraphicsComponent::draw(dp, layer);
}

void NPCGraphicsComponent::showHealth(bool keyHeld) {
    showHealth_ = keyHeld;
}

QPixmap * NPCGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

void NPCGraphicsComponent::animate() {
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ > arrayIndexMax_ ? pixmapIndex_ = arrayIndexMin_
            : pixmapIndex_;
        setImgIndex(pixmapIndex_);

    }
}

} /* end namespace td */
