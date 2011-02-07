#include "PlayerGraphicsComponent.h"
#include "Player.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(QWidget* gui) 
:       GraphicsComponent(gui) {}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::update(Player* player) {
    QPoint pos = player->GetPos();
    
    QPainter p(gui_);
    p.drawLine(0, 0, 100, 100);
}

