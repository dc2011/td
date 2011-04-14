#ifndef TD_CONTEXTMENUTYPES_H
#define TD_CONTEXTMENUTYPES_H

#include "ContextMenu.h"
#include "Player.h"

namespace td {

/**
 * The context menu for building a tower.
 */
class BuildContextMenu : public ContextMenu {
    Q_OBJECT

public:
    BuildContextMenu(Player* player);
    
    /**
     * Select a choice in an open context menu.
     *
     * @author Dean Morin
     * @param keyPressed The numerical key that was pressed.
     */
    virtual void selectMenuItem(int keyPressed);

signals:
    /**
     * Emitted when an tower is selected to be built.
     *
     * @author Dean Morin
     * @param towerType The type of tower to be built.
     * @param pos Where to build the tower.
     */
    void signalTowerSelected(int towerType, QPointF pos);
};

/**
 * The context menu for upgrading or selling a tower.
 */
class TowerContextMenu : public ContextMenu {
    Q_OBJECT

public:
    TowerContextMenu(Player* player);
    
    /**
     * Select a choice in an open context menu.
     *
     * @author Dean Morin
     * @param keyPressed The numerical key that was pressed.
     */
    virtual void selectMenuItem(int keyPressed);

signals:
    /**
     * Emitted when a tower should be sold.
     *
     * @author Dean Morin
     * @param pos Where the tower to sell is.
     */
    void signalSellTower(QPointF pos); 
};

/**
 * The context menu for upgrading a player.
 */
class PlayerContextMenu : public ContextMenu {
    Q_OBJECT

public:
    PlayerContextMenu(Player* player);
    
    /**
     * Select a choice in an open context menu.
     *
     * @author Dean Morin
     * @param keyPressed The numerical key that was pressed.
     */
    virtual void selectMenuItem(int keyPressed);
};

} // end namespace td

#endif

