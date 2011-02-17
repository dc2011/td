#include "PlayerGraphicsComponent.h"
#include "Player.h"

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
        DrawParams* dp = (DrawParams*) malloc(sizeof(DrawParams));

        dp->pos     = player->getPos();
        dp->moving  = player->getVelocity().length() != 0;
        //dp->scale   = player->getScale();
        dp->scale   = 1;
        //dp->degrees = player->getOrientation();
        dp->degrees = 90;
        
        qDebug("PlayerGraphicsComponent::update");        
        emit signalDraw(dp, this);
    }
}

