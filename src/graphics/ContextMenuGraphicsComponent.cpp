#include "ContextMenuGraphicsComponent.h"
#include "../engine/ContextMenu.h"
#include "../engine/Player.h"

#define ARROW_TOWER_SELECTED    49
#define CANNON_TOWER_SELECTED   50
#define FLAME_TOWER_SELECTED    51
#define TAR_TOWER_SELECTED      52
#define FLAK_TOWER_SELECTED     53

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
    pixmapImgs = new QPixmap[PIX_CONTEXT_MENU_MAX];
    pixmapIndex = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T1;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T2;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T3;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T4;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T5;
    pixmapIndex = 0;
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
    case ARROW_TOWER_SELECTED:
        setImgIndex(2);
        break;
    case CANNON_TOWER_SELECTED:
        setImgIndex(3);
        break;
    case FLAME_TOWER_SELECTED:
        setImgIndex(4);
        break;
    case TAR_TOWER_SELECTED:
        setImgIndex(5);
        break;
    case FLAK_TOWER_SELECTED:
        setImgIndex(6);
        break;
    }

    closeTimer_.start(500);
    scaleFactor_ = 1;

    update(NULL);
}

void ContextMenuGraphicsComponent::hideMenu() {
    menuPos_.setX(OFFSCREEN);
    menuPos_.setY(OFFSCREEN);

    update(NULL);
}

void ContextMenuGraphicsComponent::animate() {
    scaleFactor_ += 0.2;

    if(scaleFactor_ == 1) {
        animateDisconnect();
	return;
    }
    update(NULL);
}

void ContextMenuGraphicsComponent::hideSelectMenu() {
    closeTimer_.stop();
    hideMenu();
}

void ContextMenuGraphicsComponent::showResources(bool show) {
    if (show) {
        qDebug("ContextMenuGraphicsComponent::showResources; show = true");
        setImgIndex(1);
    } else {
        qDebug("ContextMenuGraphicsComponent::showResources; show = false");
        setImgIndex(0);
    }

    scaleFactor_ = 1;

    update(NULL);
}

} /* end namespace td */
