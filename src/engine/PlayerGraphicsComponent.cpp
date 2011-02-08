#include "PlayerGraphicsComponent.h"
#include "Player.h"

PlayerGraphicsComponent::PlayerGraphicsComponent()
        : GraphicsComponent()
{
    /* Do init-type stuff here */
    connect(this, SIGNAL(pixmapped()), this, SLOT(onPixmapped()));
}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(Player* player) {
    if (getPixmapItem() != NULL) {
        // connect(); send update signal to graphics thread 
        getPixmapItem()->rotate(1);
    }
}

void PlayerGraphicsComponent::onPixmapped() {
    QGraphicsPixmapItem* itm = getPixmapItem();

    if (itm != NULL) {
        itm->setPixmap(QPixmap("/home/dpogue/.face"));
    }
}

