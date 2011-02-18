#ifndef CDRIVER_H
#define CDRIVER_H
#include <QTimer>
#include <QApplication>
#include <QMainWindow>
#include <QVector>
#include "ContextMenu.h"
#include "Player.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "../client/MainWindow.h"
#include "../graphics/ContextMenuGraphicsComponent.h"
#include "../graphics/PlayerGraphicsComponent.h"
#include "../network/netclient.h"
#include "../network/stream.h"
#include "Unit.h"
#include "GameObject.h"
namespace td {
  class CDriver : public QObject {
      Q_OBJECT
  
  private:
    QTimer* gameTimer_;
    Player* human_;
    MainWindow* mainWindow_;
    /**
     * A context menu that appears around the player.
     */
    ContextMenu* contextMenu_;
  public:
    // ctors and dtors
    CDriver(MainWindow* parent = 0);
    ~CDriver();

    /**
     * Creates a human player object.
     * Sets event filter for key presses to be passed to PlayerInputComponent.
     * 
     * @author Tom Nightingale
     * @return Player*, pointer to new player instance.
     */
    Player* createHumanPlayer(MainWindow *);

    /**
     * Connects all current GameObjects' SLOTs to a timer SIGNAL.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void bindAll();

    /**
     * Connects the client driver to the server. This must be called
     * at some point before the updateServer() method is ever called,
     * as it creates the stream that updateServer() uses to push updates
     * to the server.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    static void connectToServer(char * servaddr);
    /**
     * Disconnects the client driver from the server,
     * and destroys the stream used to update the server, call this on cleanup.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    static void disconnectFromServer();

   /**
     * Sends client updates to the server, static method, this
     * call this method from the update() function of the GameObject
     * whose state you want to send to the server.
     * 
     * @author Duncan Donaldson
     * @param u the unit object whose state is to be sent to the server.
     *
     * @return void
     */
    static void updateServer(Unit* u);

    /**
     * Reads position updates from the server for a player object.
     *
     * @author Duncan Donaldson
     * @param u the unit object to be updated with server info.
     *
     * @return void
     */
    static void updatePlayer(Unit* u);

    /**
     * Stop game timer.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void endGame();
    
    /**
     * Load map from file, parse data, store in game info map property
     * 
     * @author Duncan Donaldson
     * @return int
     */
    //int loadMap(GameInfo &gi, char* map);
    
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
  };
}
#endif
