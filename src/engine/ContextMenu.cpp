#include "ContextMenu.h"
#include "../audio/SfxManager.h"
#include "../graphics/ContextMenuGraphicsComponent.h"
#include "../util/defines.h"
#include "../engine/Tile.h"
#include "../engine/CDriver.h"
#include "../engine/Map.h"

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
        PLAY_LOCAL_SFX(SfxManager::contextMenuOpened);
        //qDebug("opens a menu");
        menuIsOpen_ = true;	
        emit signalPlayerMovement(false);
        ((ContextMenuGraphicsComponent*)graphics_)->showMenu(player_->getPos());
    } else {
        PLAY_LOCAL_SFX(SfxManager::contextMenuClosed);
        //qDebug("closes a menu");
        menuIsOpen_ = false;
        emit signalPlayerMovement(true);
        ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    }
}

void ContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_ || keyPressed < TOWER_ARROW
                     || keyPressed > TOWER_FLAK) {
        return;
    }
    PLAY_LOCAL_SFX(SfxManager::contextMenuSelect);
    //qDebug("selects a menu item");
    menuIsOpen_ = false;
    emit signalPlayerMovement(true);
    ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    ((ContextMenuGraphicsComponent*)
     graphics_)->showSelectMenu(keyPressed, player_->getPos());
    
    emit signalTowerSelected(keyPressed, player_->getPos());
}

void ContextMenu::viewResources(bool altHeld) {
    if (menuIsOpen_) {
	((ContextMenuGraphicsComponent*) graphics_)->showResources(altHeld);
    }
}

} /* end namespace td */
