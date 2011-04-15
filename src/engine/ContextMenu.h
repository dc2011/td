#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QObject>
#include <QPointF>
#include <QTimer>
#include "ClsIdx.h"

namespace td {
class ContextMenuGraphicsComponent;
class Player;

class ContextMenu : public QObject {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kContextMenu;
    }

public:
    ContextMenu(Player* player);
    virtual ~ContextMenu();

    /**
     * Gets the state of the various upgrades that can be selected through this
     * menu.
     *
     * @author Dean Morin
     * @return The state of all upgrades related to this menu.
     */
    int getUpgradeLevels() const {
        return upgradeLevels_;
    }

protected:
    /** Is responsible for rendering this object. */
    ContextMenuGraphicsComponent* graphics_;

    /** The human player on this client. Needed for position info. */
    Player* player_;

    /** True if a context menu is currently open. */
    bool menuIsOpen_;

    /** The state of all upgrades that this menu can represent. */ 
    int upgradeLevels_;

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
    virtual void selectMenuItem(int keyPressed);

    /**
     * Shows or hides the resources required to build the towers.
     * 
     * @author Dean Morin
     * @param altHeld True if the resources should be displayed.
     */
    void viewResources(bool altHeld);

signals:
    /**
     * Emitted when the menu is shown to stop the players movement.
     *
     * @author Dean Morin
     * @param move False if the player should stop moving.
     */
    void signalPlayerMovement(bool move);
};

} /* end namespace td */

#endif

