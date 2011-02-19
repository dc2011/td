#include "ContextMenuGraphicsComponent.h"
#include "../engine/Player.h"

ContextMenuGraphicsComponent::ContextMenuGraphicsComponent()
    : GraphicsComponent() {
}
void ContextMenuGraphicsComponent::update(GameObject* obj) {
    Player* player = (Player*)obj;
    DrawParams* dp = new DrawParams();
    dp->pos     = player->getPos();
    emit signalDraw(dp, this);
}

void ContextMenuGraphicsComponent::initPixmaps() {
    //TODO: add animation images here or just single img
    pixmapImgs = new QPixmap[PIX_CONTEXT_MENU_MAX];
    pixmapIndex = 0;
    pixmapImgs[pixmapIndex] = PIX_CONTEXT_MENU_0;
}

