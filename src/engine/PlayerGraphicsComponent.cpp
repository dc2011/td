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
        emit signalDraw(player->getPos(), this);
    }
}

void PlayerGraphicsComponent::draw(QPointF* pos) {
    QGraphicsPixmapItem* itm = getPixmapItem();
    
    if (itm != NULL) {
        QPixmap pix(32, 32);
        pix.fill(QColor(0, 0, 255));
        itm->setPixmap(pix);
        itm->update();
        // connect(); send update signal to graphics thread 
        itm->setOffset(*pos);
    }
}
