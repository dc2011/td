#include "PlayerInputComponent.h"
#include "Player.h"

PlayerInputComponent::PlayerInputComponent() {
    menuIsOpen_ = false;
}

PlayerInputComponent::~PlayerInputComponent() { }

void PlayerInputComponent::update() {}

void PlayerInputComponent::setParent(Unit *parent) {
    // Casting Unit* to Player*.
    parent_ = (Player*) parent;
}

void PlayerInputComponent::processDirectionKey(int eventType, int key) {
    int event = (eventType == QEvent::KeyPress) ? 1 : 0;
    QVector2D force = parent_->getForce();

    if(menuIsOpen_) {
	force.setX(0);
	force.setY(0);
	parent_->setForce(force);
	return;
    }

    
    switch (key) {
        case Qt::Key_Up:
            force.setY(event * -1);
            break;
            
        case Qt::Key_Down:
            force.setY(event);
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

void PlayerInputComponent::keyPressed(int key) {
     //qDebug("PlayerInputComponent::keyPressed(%d);", key);
    processDirectionKey(QEvent::KeyPress, key);

}

void PlayerInputComponent::keyReleased(int key) {
    //qDebug("PlayerInputComponent::keyReleased(%d)", key);
    processDirectionKey(QEvent::KeyRelease, key);
}

void PlayerInputComponent::playerMovement(bool move) {
    qDebug("Fired move");
    menuIsOpen_ = move;
}
