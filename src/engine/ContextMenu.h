#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QObject>
#include <QTimer>
#include "Player.h"
#include "../audio/manager.h"
#include "../graphics/ContextMenuGraphicsComponent.h"

#define FLAME_TOWER        49
#define CANNON_TOWER       50
#define ARROW_TOWER        51
#define TAR_TOWER          52
#define FLAK_TOWER         53

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

signals:
    /**
     * Emitted when a flame tower is selected to be built.
     */
    void signalFlameTowerSelected(QPointF);
    
    /**
     * Emitted when a flak tower is selected to be built.
     */
    void signalFlakTowerSelected(QPointF);
    
    /**
     * Emitted when a cannon tower is selected to be built.
     */
    void signalCannonTowerSelected(QPointF);
    
    /**
     * Emitted when an arrow tower is selected to be built.
     */
    void signalArrowTowerSelected(QPointF);
    
    /**
     * Emitted when a tar tower is selected to be built.
     */
    void signalTarTowerSelected(QPointF);
};

#endif

