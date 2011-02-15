#ifndef MENU_H
#define MENU_H

#include "GameObject.h"

class Menu : public QObject {
    Q_OBJECT

public:
    Menu() {}
    ~Menu() {}

    virtual void showMenu();
    virtual void hideMenu();
}

#endif

