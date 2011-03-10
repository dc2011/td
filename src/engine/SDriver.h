#ifndef SDRIVER_H
#define SDRIVER_H

#include <QTimer>
#include <QApplication>
#include <QObject>
#include <QVector>
#include <QMap>
#include <QHostAddress>
#include "ResManager.h"
#include "Player.h"
#include "../network/netserver.h"
#include "../network/stream.h"

namespace td {

class SDriver : public QObject {
    Q_OBJECT 

private:
    QTimer* waveTimer_;
    ResManager* mgr_;

public:
    // ctors and dtors
    SDriver();
    virtual ~SDriver();

    /**
     * Starts game timer, initializes network server instance,
     * also connects the onUDPReceived signal to UDPReceived slot.
     * 
     * 
     * @author Duncan Donaldson
     */
    void startGame();

    /**
     * Stop game timer, and shuts down the network server.
     * 
     * @author Duncan Donaldson
     */
    void endGame();
    /**
     * If an object exists, updates its values with the ones read.
     * otherwise creates an object.
     * 
     * @author Duncan Donaldson
     * @author Darryl Pogue
     * @return returns a reference to the game object that has 
     * been updated or created
     */
    GameObject* updateObject(Stream* s);
    /**
     * Destroys a server-side object, and tells all clients
     * to update their local copies of said object.
     * 
     * @author Duncan Donaldson
     * @param id The id of the object to be destroyed.
     */
    void destroyServerObj(int id);

public slots:
    /**
     * Spawns a server-side wave and updates all clients.
     * ****WARNING****
     * used as-is this will eventually run the server side out of memory
     * once we get further along with game logic, I will add logic to make sure
     * a previous wave has been destroyed before spawning a new one.
     * @author Duncan Donaldson
     */
    void spawnWave();
    /**
     * Handles a UDP packet receive by updating a currently existing player
     * or adding the player to the players list if the player does not exist.
     * 
     * @author Duncan Donaldson
     */
    void onUDPReceive(Stream* s);
};

} /* end namespace td */

#endif
