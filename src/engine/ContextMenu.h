#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QObject>
#include "Player.h"

class ContextMenu : public QObject {
    Q_OBJECT

public:
    ContextMenu(Player* player);
    virtual ~ContextMenu() {}

    void showMenu() {}
    void hideMenu() {}

private:
    /**
     * The human player on this client.
     */
    Player* player_;

    /**
     * True if a context menu is currently open.
     */
    bool menuIsOpen_;

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

