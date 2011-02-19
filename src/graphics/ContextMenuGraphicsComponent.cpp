#include "ContextMenuGraphicsComponent.h"
#include "../engine/Player.h"

ContextMenuGraphicsComponent::ContextMenuGraphicsComponent()
        : GraphicsComponent() {
}
void ContextMenuGraphicsComponent::update(GameObject* obj) {
    Player* player = (Player*)obj;
    //if (!player->getDirtyStatus()) //is client side doesn't really need dirty check
    //    return;
    //player->setToClean();

    QGraphicsPixmapItem* itm = getPixmapItem();
    if (itm != NULL) {
        //trimmed down should only require the position to be set.
        DrawParams* dp = new DrawParams();
        dp->pos     = player->getPos();
        emit signalDraw(dp, this);
    }
}

QPixmap ContextMenuGraphicsComponent::initPixmaps() {
    //TODO: add animation logic here?
    return QPixmap(PIX_CONTEXT_MENU_0);
}

