#include "PlayerGraphicsComponent.h"
#include "Player.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(const char* pixmap) 
:       GraphicsComponent(QPixmap(pixmap)) {
    show();    
}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::updatePosition(Player* player) {
    static int x = 0;
    static int y = 0;
    x++;
    y++;
    setPos(x, y);
   // setPos(player->GetPos());
    update();
}

