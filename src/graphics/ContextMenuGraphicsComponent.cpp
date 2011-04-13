#include "ContextMenuGraphicsComponent.h"
#include "../engine/ContextMenu.h"
#include "../engine/Player.h"
#include "../engine/CDriver.h"

#define ARROW_TOWER_SELECTED    49
#define CANNON_TOWER_SELECTED   50
#define FLAME_TOWER_SELECTED    51
#define TAR_TOWER_SELECTED      52
#define FLAK_TOWER_SELECTED     53

namespace td {

    QPixmap * ContextMenuGraphicsComponent::pixmapImgs_ = 0;

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
    dp->pixmapIdx = nextImage_;

    emit signalDraw(dp,this, LAYER_MENU);
}

void ContextMenuGraphicsComponent::draw(DrawParams* dp, int layer) {
    setImgIndex(dp->pixmapIdx);
    GraphicsComponent::draw(dp, layer);
}

void ContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_CONTEXT_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_RES;
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

    scaleFactor_ = 0;
    nextImage_ = 0;
    
    closeTimer_.stop();
    animate_ = true;

    update(NULL);
}

void ContextMenuGraphicsComponent::showSelectMenu(int type, QPointF playerPos) {
    QPointF tempMenuPos(playerPos);
    animate_ = false;

    menuPos_.setX(tempMenuPos.x());
    menuPos_.setY(tempMenuPos.y());

    switch(type) {
        //going to have some accessor to set img
    case ARROW_TOWER_SELECTED:
        nextImage_ = 2;
        break;
    case CANNON_TOWER_SELECTED:
        nextImage_ = 3;
        break;
    case FLAME_TOWER_SELECTED:
        nextImage_ = 4;
        break;
    case TAR_TOWER_SELECTED:
        nextImage_ = 5;
        break;
    case FLAK_TOWER_SELECTED:
        nextImage_ = 6;
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
    CDriver::instance()->getMainWindow()->getScene()->update();
}

void ContextMenuGraphicsComponent::animate() {

    if(scaleFactor_ == 1) {
        animate_ = false;
	return;
    }
    scaleFactor_ += 0.2;

    update(NULL);
}

void ContextMenuGraphicsComponent::hideSelectMenu() {
    closeTimer_.stop();
    hideMenu();
}

void ContextMenuGraphicsComponent::showResources(bool show) {
    if (show) {
        nextImage_ = 1;
    } else {
        nextImage_ = 0;
    }

    scaleFactor_ = 1;

    update(NULL);
}

QPixmap * ContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

} /* end namespace td */
