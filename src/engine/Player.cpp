#include "Player.h"

Player::Player(InputComponent* input, PhysicsComponent* physics) {
    QPoint v(1, 0);
    QVector2D force(0, 0);
//    SetVelocity(QVector2D(v));
    this->setForce(force);
    input_ = input;
    physics_ = physics;
}

void Player::update() {
    physics_->update(this);
}

bool Player::eventFilter(QObject *obj, QEvent *event) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    PlayerInputComponent *pInput = (PlayerInputComponent*) input_;
    // Target specific events and specific keys to handle.
    // This is:
    //      - KeyPressed
    //      - KeyRelease
    // For:
    //      - Up, Down, Left, Right
    switch (event->type()) { 
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
            switch (keyEvent->key()) {
                case Qt::Key_Up:
                case Qt::Key_Down:
                case Qt::Key_Left:
                case Qt::Key_Right:
                    pInput->processDirectionKey(this, event->type(), keyEvent->key());
                    
                    // Flag these events as handled.
                    return true;
                    
                default:
                    return QObject::eventFilter(obj, event);
            }
        default:
            return QObject::eventFilter(obj, event);
    }
}
