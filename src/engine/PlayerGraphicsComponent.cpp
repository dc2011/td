#include "PlayerGraphicsComponent.h"
#include "Player.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(const char* pixmap) 
:       GraphicsComponent(pixmap) {}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(Player* player) {
    if (getPixmapItem() != NULL) {
        // connect(); send update signal to graphics thread 
    }
}

