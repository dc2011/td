#include "NPCGraphicsComponent.h"
#include "../engine/NPC.h"
#include "../engine/CDriver.h"

namespace td {

QPixmap * NPCGraphicsComponent::pixmapImgs_ = 0;
bool NPCGraphicsComponent::showHealth_    = 0;

NPCGraphicsComponent::NPCGraphicsComponent()
        : GraphicsComponent() {
}

NPCGraphicsComponent::NPCGraphicsComponent(int npcType)
    : GraphicsComponent(), npcType_(npcType) {
    connect(CDriver::instance()->getMainWindow(),  SIGNAL(signalAltHeld(bool)),
            this, SLOT(showHealth(bool)));
    emit created(this);
}

NPCGraphicsComponent::~NPCGraphicsComponent() {
    disconnect(this);
}

void NPCGraphicsComponent::update(GameObject* obj) {
    NPC* npc = (NPC*)obj;
    if (!npc->isDirty()) {
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1;
    dp->degrees = npc->getOrientation();
    //npcHealth   = (npc->getHealth()/npc->getMaxHealth()); This is the real thing. Commented until damage works.
    npcHealth   = npcHealth - 0.003; //This and the following lines are for tests.
    if(npcHealth < 0) {
        npcHealth = 0;
    }
    //TODO: the layers will change with different NPC's
    emit signalDraw(dp, this, LAYER_FLYNPC);
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

void NPCGraphicsComponent::initPixmaps() {
    healthbarItem_ = new QGraphicsRectItem(QRectF(OFFSCREEN, OFFSCREEN, 96, 7));
    npcHealth = 1;
    CDriver::instance()->getMainWindow()->getScene()->addItem(healthbarItem_);
    if (pixmapImgs_) {
        setNonStaticValues();
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_NPC_TOTAL];
    }
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_1;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_2;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PTERO_3;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PLEA_0;
    pixmapImgs_[pixmapIndex_++] = PIX_NPC_PLEA_1;
    setNonStaticValues();
}

void NPCGraphicsComponent::setNonStaticValues() {
    switch (npcType_) {
    case NPC_PTERO:
        animateMod_ = 4;
        arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PTERO_START;
        arrayIndexMax_ = PIX_NPC_PTERO_START + PIX_NPC_PTERO_MAX - 1;

        break;
    case NPC_PLEA:
        animateMod_ = 6;
        arrayIndexMin_ = pixmapIndex_ = PIX_NPC_PLEA_START;
        arrayIndexMax_ = PIX_NPC_PLEA_START + PIX_NPC_PLEA_MAX - 1;
        break;
    }
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
