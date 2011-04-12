#ifndef DRIVER_H
#define DRIVER_H

#include <QObject>
#include <QTimer>
#include <QVector2D>
#include "ResManager.h"
#include "Map.h"

namespace td {

class Collectable;
class Tower;
class NPC;
class Projectile;
class Resource;

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
     * Notifies the driver of an update to an object.
     * On the server, this is used to build a network message to synchronize
     * the object state across clients.
     *
     * @author Darryl Pogue
     * @param obj The GameObject that has been updated.
     */
    virtual void update(GameObject* obj) = 0;

    /**
     * Notifies the driver of a real-time update to an object.
     * This is used to build a network message sent streaming to other
     * clients to synchronize the object state.
     *
     * @author Darryl Pogue
     * @param obj The GameObject that has been updated.
     */
    virtual void updateRT(GameObject* obj) = 0;

    /**
     * Sends an arbitrary network message.
     * If you are calling this function, you are probably doing it wrong.
     *
     * @author Darryl Pogue
     * @param msgType The type of message to be sent. (See netmessages.h)
     * @param msg The message data as a byte array.
     */
    virtual void sendNetMessage(unsigned char msgType, QByteArray msg) = 0;

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

    /**
     * Creates a new tower of the given type.
     *
     * @author Darryl Pogue
     * @param type The type of tower to create.
     * @return A pointer to the new tower.
     */
    Tower* createTower(int type);

    /**
     * Creates a new NPC of the given type.
     *
     * @author Darryl Pogue
     * @author Marcel Vangrootheest
     * @param type The type of NPC to create.
     * @return A pointer to the new NPC.
     */
    NPC* createNPC(int type);

    /**
     * Creates a projectile object.
     *
     * @author Pan Khantidhara
     * @author Marcel Vangrootheest
     * @author Dean Morin
     * @param projType The type of the projectile (Arrow, Cannon, etc).
     * @param source The starting point of the projectile.
     * @param target The destination point of the projectile.
     * @return A pointer to the created projectile.
     */
    Projectile* createProjectile(int projType, QPointF source,
            QPointF target, Unit* enemy);

    /**
     * Creates a collectable object.
     *
     * @author Dean Morin
     * @param projType The type of the collectable (resource or gem).
     * @param source The origin of the collectable.
     * @param vel The velocity of the unit that dropped the collectable.
     * @return A pointer to the created collectable.
     */
    Collectable* createCollectable(int collType, QPointF source, QVector2D vel);

    //Resource* createResource(int type);

    /**
     * Need to find object with res manager. Did I do it right?
     *
     * @author Marcel Vangrootheest
     * @param id The id to find the object with.
     */
    GameObject* findObject(unsigned int id);

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
     * Creates projectile on server and send message to client for creation.
     * Connected to fire() in TowerPhysicsComponent
     *
     * @author Marcel Vangrootheest
     * @param projType The type of the projectile (Arrow, Cannon, etc).
     * @param source The starting point of the projectile.
     * @param target The destination point of the projectile.
     */
    virtual void requestProjectile(int projType, QPointF source, 
            QPointF target, Unit* enemy);

    /**
     * Creates projectile on server and send message to client for creation.
     * Connected to signalDropResource in Player.
     *
     * @author Dean Morin
     * @param projType The type of the resource.
     * @param source The coords of the unit that dropped the collectable.
     * @param velocity The velocity of the unit that dropped the collectable.
     */
    virtual void requestCollectable(int projType, QPointF source, 
            QVector2D velocity);
};

} /* end namespace td */

#endif
