#include "PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() {}
PlayerPhysicsComponent::~PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::Update(Player* player) {
    QVector2D v = player->GetVelocity();
    // Do stuff.
    QPoint pos = player->GetPos();
    pos += QPoint(v.x() * v.length(), v.y() * v.length());
    player->SetPos(pos);
}
