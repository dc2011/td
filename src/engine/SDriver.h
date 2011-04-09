#ifndef SDRIVER_H
#define SDRIVER_H

#include <QSet>
#include <QList>
#include "Driver.h"
#include "NPCWave.h"
#include "../network/netserver.h"
#include "../util/mutex_magic.h"

namespace td {

class Player;
class Tower;
class NPC;
class Resource;

class SDriver : public Driver {
    Q_OBJECT 
    THREAD_SAFE_CLASS

private:
    NetworkServer* net_;
    QList<Player*> players_;
    QSet<GameObject*> updates_;
    QList<NPCWave*> waves_;

    /** Keeps track of how many NPCs there currently are. */
    size_t npcCounter_;

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
     * Notifies the driver of an update to an object.
     * On the server, this is used to build a network message to synchronize
     * the object state across clients.
     *
     * @author Darryl Pogue
     * @author Duncan Donaldson
     * @param obj The GameObject that has been updated.
     */
    virtual void update(GameObject* obj);

    /**
     * Notifies the driver of a real-time update to an object.
     * This is used to build a network message sent streaming to other
     * clients to synchronize the object state.
     *
     * @author Darryl Pogue
     * @author Duncan Donaldson
     * @param obj The GameObject that has been updated.
     */
    virtual void updateRT(GameObject* obj);

    /**
     * Sends an arbitrary network message to all connected clients.
     * If you are calling this function, you are probably doing it wrong.
     *
     * @author Darryl Pogue
     * @param msgType The type of message to be sent. (See netmessages.h)
     * @param msg The message data as a byte array.
     */
    virtual void sendNetMessage(unsigned char msgType, QByteArray msg);

protected slots:
    virtual void onTimerTick();

public slots:
    /**
     * Destroys a GameObject and removes it from the ResManager.
     *
     * @author Darryl Pogue
     * @author Duncan Donaldson
     * @author Dean Morin
     * @author Marcel van Grootheest
     * @param obj The GameObject to be destroyed.
     */
    virtual void destroyObject(GameObject* obj);

    /**
     * Destroys a GameObject by id  and removes it from the ResManager.
     *
     * @author Darryl Pogue
     * @author Duncan Donaldson
     * @author Dean Morin
     * @author Marcel van Grootheest
     * @param id The id of the GameObject to be destroyed.
     */
    virtual void destroyObject(int id);

    /**
     * Gets the NetworkServer object used by this SDriver.
     *
     * @author Dean Morin
     * @return The NetworkServer object used by this SDriver.
     */
    NetworkServer* getNet() {
        return net_;
    }

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
     * slot that is called to destroy an NPC when its health reaches 0.
     *
     * @author Duncan Donaldson
     */
    void deadNPC(int id);
    /**
     * Handles a UDP packet receive by updating a currently existing player
     * or adding the player to the players list if the player does not exist.
     * 
     * @author Duncan Donaldson
     */
    void onMsgReceive(Stream* s);
};

} /* end namespace td */

#endif
