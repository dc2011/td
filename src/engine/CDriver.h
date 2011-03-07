#ifndef CDRIVER_H
#define CDRIVER_H

#include <QTimer>
#include <QApplication>
#include <QMainWindow>
#include <QVector>
#include <QPointF>
#include "ResManager.h"
#include "ContextMenu.h"
#include "NPC.h"
#include "Player.h"
#include "Projectile.h"
#include "Tower.h"
#include "../client/MainWindow.h"
#include "../network/netclient.h"
#include "../network/stream.h"
#include "Unit.h"
#include "GameObject.h"
#include "Map.h"

namespace td {

class CDriver : public QObject {
    Q_OBJECT
  
private:
    /**
     * The game object resource manager.
     */
    ResManager* mgr_;
    QTimer* gameTimer_;
    Player* human_;
    MainWindow* mainWindow_;
    // The game map containing all the tiles, waypoints, and access methods
    Map* gameMap_;
    /**
     * A context menu that appears around the player.
     */
    ContextMenu* contextMenu_;
    Projectile* projectile_;
    QSet<NPC*> npc_;
    Tower* tower_;
    /** keeps track of time since last npc creation */
    size_t npcCounter_;

public:
    // ctors and dtors
    CDriver(MainWindow* parent = 0);
    ~CDriver();

    /**
     * Connects the client driver to the server. This must be called
     * at some point before the updateServer() method is ever called,
     * as it creates the stream that updateServer() uses to push updates
     * to the server.
     * 
     * @author Duncan Donaldson
     */
    void connectToServer(const QString& servaddr);

    /**
     * Disconnects the client driver from the server,
     * and destroys the stream used to update the server, call this on cleanup.
     * 
     * @author Duncan Donaldson
     */
    void disconnectFromServer();

    /**
     * Sends client updates to the server, static method, this
     * call this method from the update() function of the GameObject
     * whose state you want to send to the server.
     * 
     * @author Duncan Donaldson
     * @param obj The GameObject to transmit.
     */
    static void updateServer(GameObject* obj);

    /**
     *
     * @author Duncan Donaldson
     */
    void readObject(Stream* s);

    /**
     * Creates a human player object.
     * Sets event filter for key presses to be passed to PlayerInputComponent.
     * 
     * @author Tom Nightingale
     * @author Duncan Donaldson
     * @author Darryl Pogue
     * @return pointer to new player instance.
     */
    void createHumanPlayer(MainWindow *);

    /**
     * creates npc object
     * @author Marcel Vangrootheest
     * @returns the reference to an NPC
     */
    NPC* createNPC();

    /**
     * Stop game timer.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void endGame();
    
public slots:
    /**
    * Initialize and start game timer.
    * [Hijacked and updated by Tom Nightingale] 
    * Client side objects are created here.
    *
    * @author Duncan Donaldson
    * @return void
    */
    void startGame();

private slots:
    /**
     * Creates a projectile object.
     *
     * @author Pan Khantidhara, Marcel Vangrootheest
     */
    void createProjectile();

    /**
     * Temp testing method.
     *
     * @author Dean Morin
     */
    void createTower(int towerType, QPointF pos);

    /**
     *
     * @author Duncan Donaldson
     */
    void UDPReceived(Stream* s);

    /**
     * Creates Npc objects based on the game tick.
     *
     * @author Marcel Vangrootheest
     */
    void NPCCreator();
    /**
     * Deletes NPC later
     *
     * @author Marcel Vangrootheest
     */
    void NPCDeleter(Unit*);
};

} /* end namespace td */

#endif
