#ifndef DRIVER_H
#define DRIVER_H

#include <QObject>
#include <QTimer>
#include "ResManager.h"
#include "Map.h"

namespace td {

class Driver : public QObject {
    Q_OBJECT
  
protected:
    /**
     * The game object resource manager.
     */
    ResManager* mgr_;

    /**
     * The game map containing all tiles, waypoints, and access methods.
     */
    Map* gameMap_;

    /**
     * The central game timer that initiates all object updates.
     */
    QTimer* gameTimer_;

public:
    Driver();
    virtual ~Driver();

    /**
     * Gets the game map.
     *
     * @author Ian Lee
     * @return The map for the game.
     */
    Map* getGameMap() const {
        return gameMap_;
    }

    /**
     * Returns the game timer.
     *
     * @author Terence Stenvold
     * @return The game timer.
     */
    QTimer* getTimer() const {
        return gameTimer_;
    }

};

} /* end namespace td */

#endif
