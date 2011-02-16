#include "Menu.h"

void Menu::openMenu() {
    if (!menuIsOpen) {
        qDebug("opens a menu");
        menuIsOpen = true;

    } else {
        qDebug("closes a menu");
        menuIsOpen = false;
    }
}

void Menu::selectMenuItem(int keyPressed) {
    if (!menuIsOpen) {
        return;
    }
    qDebug("selects a menu item");
    menuIsOpen = false;
}

