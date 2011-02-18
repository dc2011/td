#include "PlayerGraphicsComponent.h"
#include "../engine/Player.h"

PlayerGraphicsComponent::PlayerGraphicsComponent()
        : GraphicsComponent()
{
    /* Do init-type stuff here */
}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(GameObject* obj) {
    Player* player = (Player*)obj;
    QGraphicsPixmapItem* itm = getPixmapItem();

    if (itm != NULL) {
        DrawParams* dp = new DrawParams();

        dp->pos     = player->getPos();
        dp->moving  = player->getVelocity().length() != 0;
        //dp->scale   = player->getScale();
        dp->scale   = 1;
        dp->degrees = player->getOrientation();
        
        emit signalDraw(dp, this);
    }
}

QPixmap PlayerGraphicsComponent::getCurrentPixmap() {
    //TODO: add animation logic here?
    return QPixmap(PIX_PLAYER);
}

