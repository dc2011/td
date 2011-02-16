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
        emit signalDraw(player->getPos(), this);
    }
}

void ContextMenuGraphicsComponent::draw(QPointF* pos) {
    QGraphicsPixmapItem* itm = getPixmapItem();
    
    if (itm != NULL) {
        QPixmap pix(100, 100);
        pix.fill(QColor(255, 0, 0));
        itm->setPixmap(pix);
        itm->update();
        // connect(); send update signal to graphics thread 
        itm->setOffset(*pos);
    }
}
