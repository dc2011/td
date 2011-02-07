#include "PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() : accel_(1), decel_(2), maxVelocity_(10) {}
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
    QVector2D vector = force * player->GetVelocity();

    if (vector.x() >= 0) {
        player->GetVelocity().setX(force.x() * accel_);
        if (qAbs(vector.x()) > maxVelocity_) {
            player->GetVelocity().setX(force.x() * maxVelocity_);
        }
    } else {
        player->GetVelocity().setX(force.x() * (accel_ + decel_));
    }
    if (vector.y() >= 0) {
        player->GetVelocity().setY(force.y() * accel_);
        if (qAbs(vector.y()) > maxVelocity_) {
            player->GetVelocity().setY(force.y() * maxVelocity_);
        }
    } else {
        player->GetVelocity().setY(force.y() * (accel_ + decel_));
    }
    if (force.x() == 0) {
        // deceleration towards 0
        if ((velX = player->GetVelocity().x()) > 0) {
            if ((velX - decel_) < 0) {
                velX = 0;
            } else {
                player->GetVelocity().setX(velX - decel_);
            }
        } else if ((velX = player->GetVelocity().x()) < 0) {
            if ((velX + decel_) > 0) {
                velX = 0;
            } else {
                player->GetVelocity().setX(velX + decel_);
            }
        }
    }
    if (force.y() == 0) {
        // deceleration towards 0
        if ((velY = player->GetVelocity().y()) > 0) {
            if ((velY - decel_) < 0) {
                velY = 0;
            } else {
                player->GetVelocity().setY(velY - decel_);
            }
        } else if ((velY = player->GetVelocity().y()) < 0) {
            if ((velY + decel_) > 0) {
                velY = 0;
            } else {
                player->GetVelocity().setY(velY + decel_);
            }
        }

    }
}
