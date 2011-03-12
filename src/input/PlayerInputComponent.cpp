#include "PlayerInputComponent.h"
#include "../engine/Player.h"

namespace td {

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
    QVector2D velo = parent_->getVelocity();

    if(menuIsOpen_) {
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

    QVector2D force = parent_->getForce();
    QVector2D velo = parent_->getVelocity();
        
    force.setX(0);
    force.setY(0);
    velo.setX(0);
    velo.setY(0);
    parent_->setVelocity(velo);
    parent_->setForce(force);
    
    menuIsOpen_ = move;
}

} /* end namespace td */
