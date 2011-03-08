#include "ContextMenuGraphicsComponent.h"
#include "../engine/ContextMenu.h"
#include "../engine/Player.h"

#define FLAME_TOWER        49
#define CANNON_TOWER       50
#define ARROW_TOWER        51
#define TAR_TOWER          52
#define FLAK_TOWER         53

namespace td {

ContextMenuGraphicsComponent::ContextMenuGraphicsComponent()
    : GraphicsComponent() {

    emit created(this);
    connect(&closeTimer_, SIGNAL(timeout()), this, SLOT(hideSelectMenu()));
}

void ContextMenuGraphicsComponent::update(GameObject *) {
    DrawParams *dp = new DrawParams();

    dp->scale = scaleFactor_;
    dp->degrees = 0;
    dp->pos = menuPos_;

    emit signalDraw(dp,this, LAYER_MENU);
}

void ContextMenuGraphicsComponent::initPixmaps() {
    //TODO: add animation images here or just single img
    pixmapImgs_ = new QPixmap[PIX_CONTEXT_MENU_MAX];
    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T1;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T2;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T3;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T4;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T5;
    pixmapIndex_ = 0;
}

void ContextMenuGraphicsComponent::showMenu(QPointF playerPos) {
    QPointF tempMenuPos(playerPos);

    menuPos_.setX(tempMenuPos.x());
    menuPos_.setY(tempMenuPos.y());

    setImgIndex(0);
    
    closeTimer_.stop();
    scaleFactor_ = 0;
    animateConnect();

    update(NULL);
}

void ContextMenuGraphicsComponent::showSelectMenu(int type, QPointF playerPos) {
    QPointF tempMenuPos(playerPos);
    animateDisconnect();

    menuPos_.setX(tempMenuPos.x());
    menuPos_.setY(tempMenuPos.y());

    switch(type) {
        //going to have some accessor to set img
    case FLAME_TOWER:
        setImgIndex(1);
        break;
    case CANNON_TOWER:
        setImgIndex(2);
        break;
    case ARROW_TOWER:
        setImgIndex(3);
        break;
    case TAR_TOWER:
        setImgIndex(4);
        break;
    case FLAK_TOWER:
        setImgIndex(5);
        break;
    }

    closeTimer_.start(500);
    scaleFactor_ = 0.9;

    update(NULL);
}

void ContextMenuGraphicsComponent::hideMenu() {
    menuPos_.setX(OFFSCREEN);
    menuPos_.setY(OFFSCREEN);

    update(NULL);
}

void ContextMenuGraphicsComponent::animate() {
    
    if(scaleFactor_ >= 0.5) {
        animateDisconnect();
	return;
    }

    scaleFactor_ += 0.1;

    update(NULL);
}

void ContextMenuGraphicsComponent::hideSelectMenu() {
    closeTimer_.stop();
    hideMenu();
}

void ContextMenuGraphicsComponent::showResources(bool show) {
    if (show) {
        qDebug("ContextMenuGraphicsComponent::showResources; show = true");
        //show the resources
    } else {
        qDebug("ContextMenuGraphicsComponent::showResources; show = false");
        // hide them
    }
}

} /* end namespace td */
