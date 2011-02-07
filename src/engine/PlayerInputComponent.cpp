#include "PlayerInputComponent.h"

PlayerInputComponent::PlayerInputComponent() {}

PlayerInputComponent::~PlayerInputComponent() { }

void PlayerInputComponent::update() {
    
}

void PlayerInputComponent::processDirectionKey(Unit* parent_, int eventType, int key) {
    int event = (eventType == QEvent::KeyPress) ? 1 : 0;
    QVector2D force = parent_->getForce();
    
    switch (key) {
        case Qt::Key_Up:
            force.setY(event);
            break;
            
        case Qt::Key_Down:
            force.setY(event * -1);
            break;
            
        case Qt::Key_Left:
            force.setX(event * -1);
            break;
            
        case Qt::Key_Right:
            force.setX(event);
            break;
    }
    
    parent_->setForce(force);
}
