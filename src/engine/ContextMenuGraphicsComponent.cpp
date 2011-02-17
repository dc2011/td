#include "ContextMenuGraphicsComponent.h"
#include "Player.h"

ContextMenuGraphicsComponent::ContextMenuGraphicsComponent()
        : GraphicsComponent() {
}
// TODO: these methods are copied straight from PlayerGraphicsCompenent, 
// they'll need to be altered for context menus
void ContextMenuGraphicsComponent::update(GameObject* obj) {
    Player* player = (Player*)obj;
    QGraphicsPixmapItem* itm = getPixmapItem();

    if (itm != NULL) {
        DrawParams* dp = (DrawParams*) malloc(sizeof(DrawParams));

        dp->pos     = player->getPos();
        dp->moving  = player->getVelocity().length() != 0;
        //dp->scale   = player->getScale();
        dp->scale   = 1;
        //dp->degrees = player->getOrientation();
        dp->degrees = 90;
        emit signalDraw(dp, this);
    }
}

