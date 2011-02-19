#include "ProjectileGraphicsComponent.h"
#include "../engine/Projectile.h"

ProjectileGraphicsComponent::ProjectileGraphicsComponent()
        : GraphicsComponent()
{
    /* Do init-type stuff here */
}

ProjectileGraphicsComponent::~ProjectileGraphicsComponent() {}

void ProjectileGraphicsComponent::update(GameObject* obj) {
    Projectile* projectile = (Projectile*)obj;
    //should cast it to projectile
    if (!projectile->getDirtyStatus()) //checks if object is dirty.
        return;
    projectile->setToClean();

    QGraphicsPixmapItem* itm = getPixmapItem();

    if (itm != NULL) {
        DrawParams* dp = new DrawParams();
        dp->pos     = projectile->getPos();
        dp->moving  = 1; //is always moving
        //player->getVelocity().length() != 0;
        dp->scale   = projectile->getScale(); // will likely be a constant value here
        dp->degrees = projectile->getOrientation();
        emit signalDraw(dp, this);
    }
}

QPixmap ProjectileGraphicsComponent::getCurrentPixmap() {
    //TODO: add animation logic here?
    return QPixmap(PIX_PROJECTILE);
}

