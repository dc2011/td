#include "ContextMenu.h"

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
        ((ContextMenuGraphicsComponent*)graphics_)->showMenu(player_);
    } else {
        td::AudioManager::instance()->playSfx("./sound/sfx/tar.ogg");
        qDebug("closes a menu");
        menuIsOpen_ = false;
        ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    }
}

void ContextMenu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen_ || keyPressed < 49 || keyPressed > 53) {
        return;
    }
    td::AudioManager::instance()->playSfx("./sound/sfx/tar.ogg");
    qDebug("selects a menu item");
    menuIsOpen_ = false;
    ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    ((ContextMenuGraphicsComponent*)graphics_)->showSelectMenu(keyPressed, player_);
    closeTimer.start(500);
}

void ContextMenu::hideSelectMenu() {
    td::AudioManager::instance()->playSfx("./sound/sfx/tar.ogg");
    ((ContextMenuGraphicsComponent*)graphics_)->hideMenu();
    closeTimer.stop();
}

