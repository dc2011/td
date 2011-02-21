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
        td::AudioManager::instance()->playSfx("../sound/sfx/tar.ogg");
        qDebug("opens a menu");
        menuIsOpen_ = true;
        graphics_->update(player_ ); //remove once the next line is working
    } else {
        td::AudioManager::instance()->playSfx("../sound/sfx/tar.ogg");
        qDebug("closes a menu");
        menuIsOpen_ = false;
        //((ContextMenuGraphicsComponent) graphics)->hideMenu(player_->getPos());
    }
}

void ContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_) {
        return;
    }
    qDebug("selects a menu item");
    menuIsOpen_ = false;
    //((ContextMenuGraphicsComponent) graphics)->displayMenuSelection(player_->getPos());
}

