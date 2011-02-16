#ifndef MENU_H
#define MENU_H

#include <QObject>


class Menu : public QObject {
    Q_OBJECT

public:
    Menu() {}
    virtual ~Menu() {}

    void showMenu() {}
    void hideMenu() {}

private:

    /**
     * True if a context menu is currently open.
     */
    bool menuIsOpen;

public slots:

    /**
     * Open a context menu.
     *
     * @author Dean Morin
     */
    void openMenu();
    
    /**
     * Select a choice in an open context menu.
     *
     * @author Dean Morin
     * @param keyPressed The numerical key that was pressed.
     */
    void selectMenuItem(int keyPressed);
    
};

#endif

