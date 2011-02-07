#include "PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() : accel_(1), decel_(2) {}
PlayerPhysicsComponent::~PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::Update(Player* player) {
    QVector2D v = player->GetVelocity();
    // Do stuff.
    //QPoint pos = player->GetPos();
    //pos += QPoint(v.x() * v.length(), v.y() * v.length());
    //player->SetPos(pos);
}

void PlayerPhysicsComponent::ApplyForce(Player* player) {
    int velX, velY;
    QVector2D force = player->GetAccel();
    if (force.x() == 0) {
        if ((velX = player->GetVelocity().x()) > 0) {
            if ((velX - decel_) < 0) {
                velX = 0;
            } else {
                player->GetVelocity().setX(velX - decel_);
            }
        }
    } else {

    }
    if (force.y() == 0) {

    } else {

    }
}
