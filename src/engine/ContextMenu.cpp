#include "ContextMenu.h"
#include "../audio/SfxManager.h"
#include "../graphics/ContextMenuGraphicsComponent.h"
#include "../util/defines.h"

namespace td {

ContextMenu::ContextMenu(Player* player) : player_(player) {
    graphics_   = new ContextMenuGraphicsComponent();
    menuIsOpen_ = false;
}

ContextMenu::~ContextMenu() {
    delete graphics_;
}

void ContextMenu::toggleMenu() {
    if (!menuIsOpen_) {
        PLAY_SFX(SfxManager::towerFireTar);
        qDebug("opens a menu");
        menuIsOpen_ = true;	
	emit signalPlayerMovement(true);
   	((ContextMenuGraphicsComponent*)graphics_)->showMenu(player_->getPos());
    } else {
        PLAY_SFX(SfxManager::towerFireTar);
        qDebug("closes a menu");
        menuIsOpen_ = false;
	emit signalPlayerMovement(false);
        ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    }
}

void ContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_ || keyPressed < TOWER_ARROW
                     || keyPressed > TOWER_FLAK) {
        return;
    }
    PLAY_SFX(SfxManager::towerFireTar);
    qDebug("selects a menu item");
    menuIsOpen_ = false;
    emit signalPlayerMovement(false);
    ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    ((ContextMenuGraphicsComponent*)
            graphics_)->showSelectMenu(keyPressed, player_->getPos());
    
    switch (keyPressed) {
        
        case TOWER_ARROW:
            emit signalTowerSelected(TOWER_ARROW, player_->getPos());
            break;
        case TOWER_CANNON:
            emit signalTowerSelected(TOWER_CANNON, player_->getPos());
            break;
        case TOWER_TAR:
            emit signalTowerSelected(TOWER_TAR, player_->getPos());
            break;
        case TOWER_FLAME:
            emit signalTowerSelected(TOWER_FLAME, player_->getPos());
            break;
        case TOWER_FLAK:
            emit signalTowerSelected(TOWER_FLAK,  player_->getPos());
            break;
    }
}

void ContextMenu::viewResources(bool altHeld) {
    if (menuIsOpen_) {
	((ContextMenuGraphicsComponent*) graphics_)->showResources(altHeld);
    }
}

} /* end namespace td */
