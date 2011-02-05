#include "Player.h"

using namespace std;

Player::Player(InputComponent* input, PhysicsComponent* physics)
: input_(input), physics_(physics) {
    QPoint v(1, 0);
    velocity_(v);
}

QVector2d Player::GetVelocity() {
    return velocity_;
}

void Player::SetVelocity(QVector2d& velocity) {
    velocity_(velocity);
}

void Player::Update() {
    physics_.Update(this);
}