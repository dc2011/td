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
    virtual void selectMenuItem(int keyPressed);
};

/**
 * The context menu for upgrading or selling a tower.
 */
class TowerContextMenu : public ContextMenu {
    Q_OBJECT

public:
    TowerContextMenu(Player* player);
    virtual void selectMenuItem(int keyPressed);
};

/**
 * The context menu for upgrading a player.
 */
class PlayerContextMenu : public ContextMenu {
    Q_OBJECT

public:
    PlayerContextMenu(Player* player);
    virtual void selectMenuItem(int keyPressed);
};

} // end namespace td

#endif

