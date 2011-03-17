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
#include "../util/mutex_magic.h"

namespace td {

class SDriver : public QObject {
    Q_OBJECT 
    THREAD_SAFE_CLASS

private:
    QTimer* waveTimer_;
    ResManager* mgr_;
    NetworkServer* net_;

    QList<Player*> players_;

public:
    // ctors and dtors
    SDriver();
    virtual ~SDriver();

    /**
     * Initialize the networking components and make everything run in the right
     * threads.
     * This is basically an elaborate hack to avoid QObject::moveToThread issues.
     *
     * @author Darryl Pogue
     */
    void initNetworking() {
        net_->start();
    }

    /**
     * Adds the socket to the game session and creates a new player with the
     * given nickname.
     *
     * @author Darryl Pogue
     * @param sock The socket of the user.
     * @param nickname The player nickname.
     * @return The ID of the newly created Player.
     */
    unsigned int addPlayer(QTcpSocket* sock, QString nickname);

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
     * Starts game timer, makes signal/slot connects, and sends the initial game
     * state to all clients.
     * 
     * @author Duncan Donaldson
     */
    void startGame();

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
     * Handles a packet receive by updating a currently existing player
     * or adding the player to the players list if the player does not exist.
     * 
     * @author Duncan Donaldson
     */
    void onMsgReceive(Stream* s);
};

} /* end namespace td */

#endif
