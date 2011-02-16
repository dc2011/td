#include "ContextMenuGraphicsComponent.h"
#include "Player.h"

ContextMenuGraphicsComponent::ContextMenuGraphicsComponent()
        : GraphicsComponent() {
}

void ContextMenuGraphicsComponent::update(GameObject* obj) {
    Player* player = (Player*)obj;
    QGraphicsPixmapItem* itm = getPixmapItem();

    if (itm != NULL) {
        emit signalDraw(player->getPos(), this);
    }
}

void ContextMenuGraphicsComponent::draw(QPointF* pos) {
    QGraphicsPixmapItem* itm = getPixmapItem();
    
    if (itm != NULL) {
        QPixmap pix(24, 24);
        pix.fill(QColor(0, 0, 255));
        itm->setPixmap(pix);
        itm->update();
        // connect(); send update signal to graphics thread 
        itm->setOffset(*pos);
    }
}
