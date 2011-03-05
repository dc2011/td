#include "ContextMenu.h"

ContextMenu::ContextMenu(Player* player) : player_(player) {
    graphics_   = new ContextMenuGraphicsComponent();
    menuIsOpen_ = false;
}

ContextMenu::~ContextMenu() {
    delete graphics_;
}

void ContextMenu::toggleMenu() {
    if (!menuIsOpen_) {
        td::AudioManager::instance()->playSfx("./sound/sfx/tar.ogg");
        qDebug("opens a menu");
        menuIsOpen_ = true;
   	((ContextMenuGraphicsComponent*)graphics_)->showMenu(player_);
    } else {
        td::AudioManager::instance()->playSfx("./sound/sfx/tar.ogg");
        qDebug("closes a menu");
        menuIsOpen_ = false;
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
    ((ContextMenuGraphicsComponent*)graphics_)->showSelectMenu(keyPressed, player_);
    
    switch (keyPressed) {
        case FLAME_TOWER:
            emit signalFlameTowerSelected(player_->getPos());
            break;
        case FLAK_TOWER:
            emit signalFlakTowerSelected(player_->getPos());
            break;
        case CANNON_TOWER:
            emit signalCannonTowerSelected(player_->getPos());
            break;
        case ARROW_TOWER:
            emit signalTowerSelected(0, player_->getPos());
            break;
        case TAR_TOWER:
            emit signalTarTowerSelected(player_->getPos());
            break;
    }
}

