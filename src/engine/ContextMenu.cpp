#include "ContextMenu.h"

ContextMenu::ContextMenu(Player* player) : player_(player) {
    graphics_ = new ContextMenuGraphicsComponent(); //free
}

void ContextMenu::toggleMenu() {
    if (!menuIsOpen_) {
        qDebug("opens a menu");
        menuIsOpen_ = true;
        //((ContextMenuGraphicsComponent) graphics)->showMenu();

    } else {
        qDebug("closes a menu");
        menuIsOpen_ = false;
        graphics_->update(player_); //remove once the next line is working
        //((ContextMenuGraphicsComponent) graphics)->hideMenu();
    }
}

void ContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_) {
        return;
    }
    qDebug("selects a menu item");
    menuIsOpen_ = false;
    //((ContextMenuGraphicsComponent) graphics)->displayMenuSelection();
}

