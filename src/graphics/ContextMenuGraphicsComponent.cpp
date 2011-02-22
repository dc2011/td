#include "ContextMenuGraphicsComponent.h"
#include "../engine/ContextMenu.h"
#include "../engine/Player.h"

ContextMenuGraphicsComponent::ContextMenuGraphicsComponent()
    : GraphicsComponent() {
}

void ContextMenuGraphicsComponent::update(GameObject *obj) {
    Player *player = (Player*)obj;
    QPointF tempMenuPos(player->getPos());
    DrawParams *dp = new DrawParams();

    tempMenuPos.setX(tempMenuPos.x() - 131);
    tempMenuPos.setY(tempMenuPos.y() - 171);

    dp->degrees = 0;
    dp->pos = tempMenuPos;
    emit signalDraw(dp, this);
}

void ContextMenuGraphicsComponent::initPixmaps() {
    //TODO: add animation images here or just single img
    pixmapImgs = new QPixmap[PIX_CONTEXT_MENU_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex] = PIX_CONTEXT_MENU_0;
}

