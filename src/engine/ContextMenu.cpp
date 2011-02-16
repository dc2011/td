#include "ContextMenu.h"

ContextMenu::ContextMenu(Player* player) : player_(player) {}

void ContextMenu::openMenu() {
    if (!menuIsOpen_) {
        qDebug("opens a menu");
        menuIsOpen_ = true;
        //showMenu(player_->getPos());

    } else {
        qDebug("closes a menu");
        menuIsOpen_ = false;
        //hideMenu(player_->getPos());
    }
}

void ContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_) {
        return;
    }
    qDebug("selects a menu item");
    menuIsOpen_ = false;
    //hideMenu(player_->getPos()); //change to displayMenuSelection()
}

