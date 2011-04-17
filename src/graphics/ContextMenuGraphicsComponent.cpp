#include "ContextMenuGraphicsComponent.h"
#include "../engine/CDriver.h"
#include "../engine/ContextMenu.h"
#include "../engine/Player.h"

namespace td {

ContextMenuGraphicsComponent::ContextMenuGraphicsComponent()
        : GraphicsComponent() {
    connect(&closeTimer_, SIGNAL(timeout()), this, SLOT(hideSelectMenu()));
}

void ContextMenuGraphicsComponent::update(GameObject *) {
    DrawParamsMenuGraphics* dp = new DrawParamsMenuGraphics();

    dp->scale = scaleFactor_;
    dp->degrees = 0;
    dp->pos = menuPos_;
    dp->animate = animate_;
    dp->pixmapIdx = nextImage_;

    emit signalDraw(dp,this, LAYER_MENU);
}

void ContextMenuGraphicsComponent::draw(void* dp, int layer) {
    DrawParamsMenuGraphics *dpMenu = (DrawParamsMenuGraphics*) dp;
    setImgIndex(dpMenu->pixmapIdx);
    GraphicsComponent::draw(dpMenu, layer);
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

void ContextMenuGraphicsComponent::showSelectMenu(int, QPointF playerPos) {
    QPointF tempMenuPos(playerPos);
    animate_ = false;

    menuPos_.setX(tempMenuPos.x());
    menuPos_.setY(tempMenuPos.y());

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

} /* end namespace td */
