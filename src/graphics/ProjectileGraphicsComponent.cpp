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
    if (!player->getDirtyStatus()) //checks if object is dirty.
        return;
    player->setToClean();

    QGraphicsPixmapItem* itm = getPixmapItem();

    if (itm != NULL) {
        DrawParams* dp = new DrawParams();
        dp->pos     = player->getPos();
        dp->moving  = 1; //is always moving
        //player->getVelocity().length() != 0;
        dp->scale   = player->getScale(); // will likely be a constant value here
        dp->degrees = player->getOrientation();
        emit signalDraw(dp, this);
    }
}

QPixmap PlayerGraphicsComponent::getCurrentPixmap() {
    //TODO: add animation logic here?
    return QPixmap(PIX_PROJECTILE);
}

