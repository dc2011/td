#include "PlayerGraphicsComponent.h"
#include "Player.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(const char* pixmap) 
:       GraphicsComponent(QPixmap(pixmap)) {}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(Player* player) {
    getPixmapItem()->setPos(player->getPos());
    getPixmapItem()->update();
}

