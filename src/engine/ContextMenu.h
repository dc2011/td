#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QObject>
#include <QTimer>
#include "Player.h"
#include "../audio/manager.h"
#include "../graphics/ContextMenuGraphicsComponent.h"

class ContextMenu : public QObject {
    Q_OBJECT

public:
    ContextMenu(Player* player);
    virtual ~ContextMenu();

private:
    /**
     * Is responsible for rendering this object.
     */
    GraphicsComponent* graphics_;

    /**
     * The human player on this client. Needed for position info.
     */
    Player* player_;

    /**
     * True if a context menu is currently open.
     */
    bool menuIsOpen_;

    QTimer closeTimer;

public slots:
    /**
     * Open a context menu, or close it if it already open.
     *
     * @author Dean Morin
     */
    void toggleMenu();
    
    /**
     * Select a choice in an open context menu.
     *
     * @author Dean Morin
     * @param keyPressed The numerical key that was pressed.
     */
    void selectMenuItem(int keyPressed);

    void hideSelectMenu();
};

#endif

