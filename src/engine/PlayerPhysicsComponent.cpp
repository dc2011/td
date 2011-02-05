#include "PlayerPhysicsComponent.h"

using namespace std;

PlayerPhysicsComponent::PlayerPhysicsComponent() {}

PlayerPhysicsComponent::Update(Player* player) {
    QVelocity2D v = player->GetVelocity();
    // Do stuff.
    QPoint pos = player->GetPos();
    pos.x += v.x() * v.length();
    pos.y += v.y() * v.length();
    player->SetPos(pos);
}