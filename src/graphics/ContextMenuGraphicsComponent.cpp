#include "ContextMenuGraphicsComponent.h"
#include "../engine/ContextMenu.h"
#include "../engine/Player.h"


#define FLAME_TOWER        49
#define CANNON_TOWER       50
#define ARROW_TOWER        51
#define TAR_TOWER          52
#define FLAK_TOWER         53

ContextMenuGraphicsComponent::ContextMenuGraphicsComponent()
    : GraphicsComponent() {

    emit created(this);
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
    pixmapImgs[pixmapIndex++] = PIX_CONTEXT_MENU_MAIN;
    pixmapImgs[pixmapIndex++] = PIX_CONTEXT_MENU_T1;
    pixmapImgs[pixmapIndex++] = PIX_CONTEXT_MENU_T2;
    pixmapImgs[pixmapIndex++] = PIX_CONTEXT_MENU_T3;
    pixmapImgs[pixmapIndex++] = PIX_CONTEXT_MENU_T4;
    pixmapImgs[pixmapIndex++] = PIX_CONTEXT_MENU_T5;
    pixmapIndex = 0;
}

void ContextMenuGraphicsComponent::showMenu(GameObject *obj) {
    Player *player = (Player*)obj;
    QPointF tempMenuPos(player->getPos());

    menuPos.setX(tempMenuPos.x() - 33);
    menuPos.setY(tempMenuPos.y() - 43);

    setImgIndex(0);

    scaleFactor = 0;
    animateConnect();

    update(NULL);
}

void ContextMenuGraphicsComponent::showSelectMenu(int type, GameObject *obj) {

    Player *player = (Player*)obj;
    QPointF tempMenuPos(player->getPos());

    menuPos.setX(tempMenuPos.x() - 33);
    menuPos.setY(tempMenuPos.y() - 43);

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

    scaleFactor = 0.5;
    animateDisconnect();

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
        animateDisconnect();
    }

    update(NULL);
}
