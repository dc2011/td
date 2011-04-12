#ifndef PLAYER_H
#define PLAYER_H

#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "../input/PlayerInputComponent.h"
#include "CollisionComponent.h"
#include "Effect.h"
#include "../graphics/PlayerGraphicsComponent.h"
#include "../physics/PlayerPhysicsComponent.h"

//TEMP
#include "../engine/Collectable.h"
namespace td {

class Player : public Unit {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kPlayer;
    }

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2),
        kNickname       = (1 << 3),
        kResource       = (1 << 4)
    };

public:
    Player(QObject* parent = 0);
    virtual ~Player() {}
//TEMP
Collectable* collectable_;
    /**
     * Reads the object state from a network stream.
     * You should assign to variables directly inside this function, rather
     * than using mutator methods to change the values.
     *
     * @author Darryl Pogue
     * @param s The network stream.
     */
    virtual void networkRead(td::Stream* s);

    /**
     * Writes the object state to a network stream.
     *
     * @author Darryl Pogue
     * @param s The network stream.
     */
    virtual void networkWrite(td::Stream* s);

    /**
     * This function will do any component initialization whenever
     * a gameobject is created.
     *
     * @author Darryl Pogue
     */
    virtual void initComponents();

    virtual void update();

    /**
     * Gets the player's nickname.
     *
     * @author Darryl Pogue
     * @return The player's nickname.
     */
    QString getNickname() const {
        return nickname_;
    }

    /**
     * Sets the nickname associated with this player.
     *
     * @author Darryl Pogue
     * @param nick The nickname of the player.
     */
    void setNickname(QString& nick) {
        nickname_ = nick;
        setDirty(kNickname);
    }

    /**
      * Gets the player's harvest coutndown.
      *
      * @author Nick Huber
      * @return The player's remaining countdown for harvesting.
      */
    int getHarvestCountdown() {
        return harvestCountdown_;
    }

private: 
    /**
     * Checks to see if the resource being harvested is ready to be picked up.
     *
     * @author Dean Morin
     */
    void harvestResource();

public slots:
    /**
     * Add effect to the effect list.
     * Replaces effect if type already exists in list.
     *
     * @author Pan K.
     * @author Marcel Vangrootheest
     * @param type Type of effect.
     */
    void createEffect(Effect* effect);

    /**
     * Remove effect from the effect list.
     *
     * @author Pan K.
     * @author Marcel Vangrootheest
     * @param effect Effect to delete.
     */
    void deleteEffect(Effect* effect);

    /**
     * Sets the boolean that determines whether or not the player's nickname
     * should be displayed.
     *
     * @author Dean Morin
     * @param keyHeld True if the alt key is being held down.
     */
    void showName(bool keyHeld) {
        ((PlayerGraphicsComponent*) graphics_)->setShowName(keyHeld);
        setDirty(1);
    }

    /**
     * Starts harvesting a resource. This will cause update() to call
     * harvestResource().
     *
     * @author Dean Morin
     * @param type The type of resource being harvested.
     */
    void startHarvesting(int type);

    /**
     * Stops a harvesting attempt partway through, if one is being attempted.
     *
     * @author Dean Morin
     */
    void stopHarvesting();

    /**
     * Drops whatever resource that the player is carrying.
     *
     * @author Dean Morin
     */
    void dropResource();

private:
    QList<Effect> effects_;

    /** Nickname associated with this player for display purposes and chat. */
    QString nickname_;

    /** The resource (if any) that the player is currently harvesting. */
    int harvesting_;

    /** How many game ticks remaining before a resource is harvested. */ 
    int harvestCountdown_;

    /** The resource (if any) that the player is currently carrying. */
    int resource_;

signals:
    /**
     * Signals that the effect list is empty (necessary so we don't spam SFX).
     *
     * Connected to okayToPlayCollisionSfx() in PlayerPhysicsComponent.
     *
     * @author Dean Morin
     */
    void signalEmptyEffectList();
    
    /**
     * Emitted when the player starts or stops harvesting a resource.
     *
     * Connected to playerMovement() in PlayerInputComponent.cpp. 
     *
     * @author Dean Morin
     * @param move False if the player should stop moving.
     */
    void signalPlayerMovement(bool move);

    /**
     * Emmitted when the player drops the resource that they are carrying.
     *
     * Connected to requestCollectable() in the driver.
     *
     * @author Dean Morin
     * @param type The resource type.
     * @param pos The player's coords when he drops the resource.
     * @param velocity The player's velocity when he drops the resource.
     */
    void signalDropResource(int type, QPointF pos, QVector2D velocity);
};

}

#endif
