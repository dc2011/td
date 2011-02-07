#include "PlayerGraphicsComponent.h"
#include "Player.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(QObject* gui) 
:       GraphicsComponent(gui) {}

PlayerGraphicsComponent::~PlayerGraphicsComponent() {}

void PlayerGraphicsComponent::Update(Player* player) {
    QPoint pos = player->GetPos();
    gui_->repaint();
}

