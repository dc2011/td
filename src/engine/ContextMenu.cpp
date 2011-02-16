#include "ContextMenu.h"

ContextMenu::ContextMenu(GraphicsComponent* graphics, Player* player) 
        : graphics_(graphics), player_(player) {}

void ContextMenu::toggleMenu() {
    if (!menuIsOpen_) {
        qDebug("opens a menu");
        menuIsOpen_ = true;
        graphics_->update(player_);
        //((ContextMenuGraphicsComponent) graphics)->showMenu();

    } else {
        qDebug("closes a menu");
        menuIsOpen_ = false;
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

