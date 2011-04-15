#include "ContextMenu.h"
#include "CDriver.h"
#include "Map.h"
#include "Player.h"
#include "Tile.h"
#include "../audio/SfxManager.h"
#include "../graphics/ContextMenuGraphicsComponent.h"
#include "../util/defines.h"

namespace td {

ContextMenu::ContextMenu(Player* player) : player_(player), upgradeLevels_(0) {
    menuIsOpen_ = false;
}

ContextMenu::~ContextMenu() {
    delete graphics_;
}

void ContextMenu::toggleMenu() {
    if (!menuIsOpen_) {
        PLAY_LOCAL_SFX(SfxManager::contextMenuOpened);
        menuIsOpen_ = true;	
        emit signalPlayerMovement(false);
        ((ContextMenuGraphicsComponent*)graphics_)->showMenu(player_->getPos());
    } else {
        PLAY_LOCAL_SFX(SfxManager::contextMenuClosed);
        menuIsOpen_ = false;
        emit signalPlayerMovement(true);
        ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    }
}

void ContextMenu::selectMenuItem(int keyPressed) {
    PLAY_LOCAL_SFX(SfxManager::contextMenuSelect);
    menuIsOpen_ = false;
    emit signalPlayerMovement(true);
    ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    ((ContextMenuGraphicsComponent*) graphics_)->showSelectMenu(keyPressed, 
            player_->getPos());
}

void ContextMenu::viewResources(bool altHeld) {
    if (menuIsOpen_) {
        ((ContextMenuGraphicsComponent*) graphics_)->showResources(altHeld);
    }
}

} /* end namespace td */
