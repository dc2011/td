#include "Player.h"

using namespace std;

Player::Player(InputComponent* input, PhysicsComponent* physics) {
    QPoint v(1, 0);
    velocity_ = QVector2D(v);

    input_ = input;
    physics_ = physics;
}

QVector2D& Player::GetVelocity() {
    return velocity_;
}

void Player::SetVelocity(QVector2D& velocity) {
    velocity_ = velocity;
}

void Player::Update() {
    physics_->Update(this);
}
