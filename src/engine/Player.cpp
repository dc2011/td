#include "Player.h"

using namespace std;

Player::Player(InputComponent* input, PhysicsComponent* physics) {
    QPoint v(1, 0);
//    SetVelocity(QVector2D(v));

    input_ = input;
    physics_ = physics;
}

void Player::Update() {
    physics_->Update(this);
}
