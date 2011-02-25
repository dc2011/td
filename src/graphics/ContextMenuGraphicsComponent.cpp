#include "ContextMenuGraphicsComponent.h"
#include "../engine/ContextMenu.h"
#include "../engine/Player.h"

#define ANIMATION_TIMEOUT  25
#define FLAME_TOWER        49
#define CANNON_TOWER       50
#define ARROW_TOWER        51
#define TAR_TOWER          52
#define FLAK_TOWER         53

ContextMenuGraphicsComponent::ContextMenuGraphicsComponent()
    : GraphicsComponent() {
    imageIndex = 0;

    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
}

void ContextMenuGraphicsComponent::update(GameObject *) {
    DrawParams *dp = new DrawParams();

    dp->scale = scaleFactor;
    dp->degrees = 0;
    dp->pos = menuPos;

    emit signalDraw(dp, this);
}

void ContextMenuGraphicsComponent::initPixmaps() {
    //TODO: add animation images here or just single img
    pixmapImgs = new QPixmap[PIX_CONTEXT_MENU_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex] = PIX_CONTEXT_MENU_MAIN;
    pixmapIndex++;
    pixmapImgs[pixmapIndex] = PIX_CONTEXT_MENU_T1;
    pixmapIndex++;
    pixmapImgs[pixmapIndex] = PIX_CONTEXT_MENU_T2;
    pixmapIndex++;
    pixmapImgs[pixmapIndex] = PIX_CONTEXT_MENU_T3;
    pixmapIndex++;
    pixmapImgs[pixmapIndex] = PIX_CONTEXT_MENU_T4;
    pixmapIndex++;
    pixmapImgs[pixmapIndex] = PIX_CONTEXT_MENU_T5;
    pixmapIndex = 0;
}

void ContextMenuGraphicsComponent::showMenu(GameObject *obj) {
    Player *player = (Player*)obj;
    QPointF tempMenuPos(player->getPos());

    menuPos.setX(tempMenuPos.x() - 33);
    menuPos.setY(tempMenuPos.y() - 43);

    imageIndex = 0;

    scaleFactor = 0;

    animationTimer.start(ANIMATION_TIMEOUT);

    update(NULL);
}

void ContextMenuGraphicsComponent::showSelectMenu(int type, GameObject *obj) {

    Player *player = (Player*)obj;
    QPointF tempMenuPos(player->getPos());

    menuPos.setX(tempMenuPos.x() - 33);
    menuPos.setY(tempMenuPos.y() - 43);

    switch(type) {
    case FLAME_TOWER:
        imageIndex = 1;
        break;
    case CANNON_TOWER:
        imageIndex = 2;
        break;
    case ARROW_TOWER:
        imageIndex = 3;
        break;
    case TAR_TOWER:
        imageIndex = 4;
        break;
    case FLAK_TOWER:
        imageIndex = 5;
        break;
    }

    scaleFactor = 0;

    animationTimer.start(ANIMATION_TIMEOUT);

    update(NULL);
}

void ContextMenuGraphicsComponent::hideMenu() {
    menuPos.setX(OFFSCREEN);
    menuPos.setY(OFFSCREEN);

    update(NULL);
}

void ContextMenuGraphicsComponent::animate() {

    scaleFactor += 0.1;

    if(scaleFactor == 0.5) {
        animationTimer.stop();
    }

    update(NULL);
}
