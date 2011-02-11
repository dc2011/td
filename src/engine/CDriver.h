#ifndef CDRIVER_H
#define CDRIVER_H
#include <QTimer>
#include <QApplication>
#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QFileDialog>
#include "Player.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerGraphicsComponent.h"
#include "../client/MainWindow.h"
#include "../network/netclient.h"
#include "../network/stream.h"
//#include "GameInfo.h"
#include "GameObject.h"
namespace td {
  class CDriver : public QObject {
      Q_OBJECT
  
  private:
    QTimer* gameTimer_;
    Player* human_;
    MainWindow* mainWindow_;
  public:
    static td::Stream* updates_;
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
     * @param v the data to send (CHANGE THIS LATER).
     *
     * @return void
     */
    static void updateServer(int data);

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
    * 
    * @author Duncan Donaldson
    * @return void
    */
    void startGame();
  };
}
#endif
