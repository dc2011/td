#ifndef SDRIVER_H
#define SDRIVER_H

#include <QSet>
#include <QList>
#include "Driver.h"
#include "NPCWave.h"
#include "Parser.h"
#include "../network/netserver.h"
#include "../util/mutex_magic.h"

namespace td {

class Collectable;
class Player;
class Tower;
class NPC;
class Resource;

class SDriver : public Driver {
    Q_OBJECT 
    THREAD_SAFE_CLASS

private:
    NetworkServer* net_;
    QMap<QTcpSocket*, Player*> players_;
    QSet<GameObject*> updates_;
    QList<NPCWave*> waves_;
    QTimer* waveTimer_;
    unsigned int timeCount_;
    unsigned int completedWaves_;
    unsigned int totalWaves_;

    /** Keeps track of how many NPCs there currently are. */
    size_t npcCounter_;

    /** The script parser to go along with the map. */
    Parser* script_;

    /** Hack to store the map name for redundancy. */
    QString mapname_;

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
     * @param success true if the game was won, false otherwise.
     */
    void endGame(bool success);

    /**
     * Sets the game map and script parser.
     * DO NOT CALL THIS AFTER A GAME HAS STARTED!!!
     *
     * @author Darryl Pogue
     * @param mapfile The filename of the map.
     */
    void setMap(QString mapfile) {
        if (script_ != NULL) {
            delete script_;
        }
        if (gameMap_ != NULL) {
            delete gameMap_;
        }
        //qDebug("%s", mapfile.toAscii().data());

        mapname_ = mapfile;

        QString scr = QString("./maps/") + mapfile;
        script_ = new Parser(this, scr);

        QString map = QString("./maps/") + script_->map + QString(".tmx");
        //qDebug() << map;

        gameMap_ = new Map(map, this);
        gameMap_->initMap();
    }

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

    /**
     * Sets the health of the player's base.
     *
     * @author Darryl Pogue
     * @param health The new base health.
     */
    virtual void setBaseHealth(int health);
    
    /**
     * Writes a message to either drop a resource or add it
     * to the Building Stage.
     *
     * @author Marcel Vangrootheest
     * @param t The BuildingTower to add the resource to.
     * @param player The player that needs to drop the resource.
     * @param drop true if the resource will always be dropped.
     */
    void towerDrop(BuildingTower* t, Player* player, bool drop);

signals:
    /**
     * Signal emitted when there are no more players in this game session.
     */
    void disconnecting();

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
     * @param multicast Whether this server sends multicast messages.
     */
    void startGame(bool multicast);

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
     * Called when a wave is destroyed; either when all of it's NPCs have been
     * killed or when the last one has reached the home base.
     *
     * Increments the completed wave counter.
     *
     * @author Tom Nightingale
     */
    void endWave();

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

    /**
     * Creates projectile on server and send message to client for creation.
     * Connected to fire() in TowerPhysicsComponent
     *
     * @author Marcel Vangrootheest
     * @param projType The type of the projectile (Arrow, Cannon, etc).
     * @param source The starting point of the projectile.
     * @param target The destination point of the projectile.
     */
    void requestProjectile(int projType, QPointF source,
            QPointF target, Unit* enemy);

    /**
     * Creates collectable on server and send message to client for creation.
     *
     * @author Dean Morin
     * @param projType The type of the collectable (resource or gem).
     * @param source The origin of the collectable.
     * @param vel The velocity of the dropper.
     */
    void requestCollectable(int collType, QPointF source, QVector2D vel);

    /**
     * Let other players know when a player has quit.
     *
     * @author Darryl Pogue
     * @param sock The socket of the player.
     */
    void playerQuit(QTcpSocket* sock);
};

} /* end namespace td */

#endif
