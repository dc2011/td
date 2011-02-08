#include "PlayerGraphicsComponent.h"
#include "Player.h"

PlayerGraphicsComponent::PlayerGraphicsComponent()
        : GraphicsComponent()
{
    /* Do init-type stuff here */
    connect(this, SIGNAL(pixmapped()), this, SLOT(onPixmapped()));
}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(GameObject* obj) {
    if (getPixmapItem() != NULL) {
        // connect(); send update signal to graphics thread 
        getPixmapItem()->rotate(1);
    }
}

void PlayerGraphicsComponent::onPixmapped() {
    QGraphicsPixmapItem* itm = getPixmapItem();

    if (itm != NULL) {
        qDebug("QGPI has been set... load an image");
        QPixmap pix(100, 100);
        pix.fill(QColor(0, 0, 255));
        itm->setPixmap(pix);
        itm->update();
    }
}

