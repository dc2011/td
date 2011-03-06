#include "ContextMenu.h"

namespace td {

ContextMenu::ContextMenu(Player* player) : player_(player) {
    graphics_   = new ContextMenuGraphicsComponent();
    menuIsOpen_ = false;

    connect(&closeTimer, SIGNAL(timeout()), this, SLOT(hideSelectMenu()));
}

ContextMenu::~ContextMenu() {
    delete graphics_;
}

void ContextMenu::toggleMenu() {
    if (!menuIsOpen_) {
        td::AudioManager::instance()->playSfx("./sound/sfx/tar.ogg");
        qDebug("opens a menu");
        menuIsOpen_ = true;	
        closeTimer.stop();
	emit signalPlayerMovement(true);
   	((ContextMenuGraphicsComponent*)graphics_)->showMenu(player_->getPos());
    } else {
        td::AudioManager::instance()->playSfx("./sound/sfx/tar.ogg");
        qDebug("closes a menu");
        menuIsOpen_ = false;
	emit signalPlayerMovement(false);
        ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    }
}

void ContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_ || keyPressed < FLAME_TOWER 
                     || keyPressed > FLAK_TOWER) {
        return;
    }
    td::AudioManager::instance()->playSfx("./sound/sfx/tar.ogg");
    qDebug("selects a menu item");
    menuIsOpen_ = false;
    ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    ((ContextMenuGraphicsComponent*)
            graphics_)->showSelectMenu(keyPressed, player_->getPos());
    emit signalPlayerMovement(false);
    closeTimer.start(800);
    
    switch (keyPressed) {
        //change tower type to macros once they're defined in the 
        //resource manager
        case FLAME_TOWER:
            //emit signalTowerSelected(0, player_->getPos());
            break;
        case FLAK_TOWER:
            //emit signalTowerSelected(1, player_->getPos());
            break;
        case CANNON_TOWER:
            //emit signalTowerSelected(2, player_->getPos());
            break;
        case ARROW_TOWER:
            emit signalTowerSelected(3, player_->getPos());
            break;
        case TAR_TOWER:
            //emit signalTowerSelected(4, player_->getPos());
            break;
    }
}

void ContextMenu::hideSelectMenu() {
    td::AudioManager::instance()->playSfx("./sound/sfx/tar.ogg");
    ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    closeTimer.stop();
}

void ContextMenu::viewResources(bool altHeld) {
    if (menuIsOpen_) {
        ((ContextMenuGraphicsComponent*) graphics_)->showResources(altHeld);
    }
}

} /* end namespace td */
