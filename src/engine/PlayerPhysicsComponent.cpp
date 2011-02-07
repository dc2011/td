#include "PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent() : accel_(1), decel_(2), maxVelocity_(10) {}
PlayerPhysicsComponent::~PlayerPhysicsComponent() {}

void PlayerPhysicsComponent::Update(Player* player) {
    this->ApplyForce(player);
    this->ApplyVelocity(player);
}

/* applies velocity to position, currently moves past bounds */
void PlayerPhysicsComponent::ApplyVelocity(Player * player) {
    QPoint newPos = player->GetPos() + player->GetVelocity().toPoint();
    player->SetPos(newPos);
}

void PlayerPhysicsComponent::ApplyForce(Player* player) {
    int velX, velY;
    QVector2D force = player->GetForce();
    QVector2D vector = force * player->GetVelocity();

    if (vector.x() >= 0) {
        player->GetVelocity().setX(force.x() * accel_ + player->GetVelocity().x());
        if (qAbs(vector.x()) > maxVelocity_) {
            player->GetVelocity().setX(force.x() * maxVelocity_);
        }
    } else {
        player->GetVelocity().setX(force.x() * (accel_ + decel_) + player->GetVelocity().x());
    }
    if (vector.y() >= 0) {
        player->GetVelocity().setY(force.y() * accel_ + player->GetVelocity().y());
        if (qAbs(vector.y()) > maxVelocity_) {
            player->GetVelocity().setY(force.y() * maxVelocity_);
        }
    } else {
        player->GetVelocity().setY(force.y() * (accel_ + decel_) + player->GetVelocity().y());
    }
    if (force.x() == 0) {
        // deceleration towards 0
        if ((velX = player->GetVelocity().x()) > 0) {
            if ((velX - decel_) < 0) {
                player->GetVelocity().setX(0);
            } else {
                player->GetVelocity().setX(velX - decel_);
            }
        } else if ((velX = player->GetVelocity().x()) < 0) {
            if ((velX + decel_) > 0) {
                player->GetVelocity().setX(0);
            } else {
                player->GetVelocity().setX(velX + decel_);
            }
        }
    }
    if (force.y() == 0) {
        // deceleration towards 0
        if ((velY = player->GetVelocity().y()) > 0) {
            if ((velY - decel_) < 0) {
                player->GetVelocity().setY(0);
            } else {
                player->GetVelocity().setY(velY - decel_);
            }
        } else if ((velY = player->GetVelocity().y()) < 0) {
            if ((velY + decel_) > 0) {
                player->GetVelocity().setY(0);
            } else {
                player->GetVelocity().setY(velY + decel_);
            }
        }

    }
}
