#ifndef PLAYER_H
#define PLAYER_H

#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "../input/PlayerInputComponent.h"
#include "Effect.h"
#include "Tile.h"
#include "../graphics/PlayerGraphicsComponent.h"
#include "../physics/PlayerPhysicsComponent.h"

namespace td {

class Player : public Unit {
    Q_OBJECT

public:
    Tile* tileThatPlayerIsOn_;
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
        kResource       = (1 << 4),
        kMoving         = (1 << 5)
    };

public:
    Player(QObject* parent = 0);
    virtual ~Player();

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

    /**
      * Sets the player's maximum harvest countdown amount.
      *
      * @author Marcel Vangrootheest
      * @param count The new harvestTime_ value.
      */
    void setHarvestTime(int time) {
        harvestTime_ = time;
        harvestCountdown_ = time;
    }

    /**
      * Sets the player's maximum harvest countdown amount.
      *
      * @author Marcel Vangrootheest
      * @return The maximum harvest countdown amount.
      */
    int getHarvestTime() {
        return harvestTime_;
    }

    /**
     * Gets the player's resource it is carrying.
     *
     * @author Marcel Vangrootheest
     * @return The player's current resource.
     */
    int getResource() {
        return resource_;
    }

    /**
     * Sets the resource that the player is carrying.
     *
     * @author Darryl Pogue
     * @param resource The resource type.
     */
    void setResource(int resource) {
        resource_ = resource;
        setDirty(kResource);
    }

    /**
     * Sets the player's stunUpgrade to true or false.
     *
     * @author Marcel Vangrootheest
     * @param stun True will cause a stun upgrade.
     */
    void setStunUpgrade(bool stun) {
        stunUpgrade_ = stun;
    }

    /**
     * Gets whether the player is moving or not.
     *
     * @author Darryl Pogue
     * @return true if the player is moving; false otherwise.
     */
    bool getMoving() const {
        return isMoving_;
    }

    /**
     * Return true if the player has the specified effect type.
     *
     * @author Marcel Vangrootheest
     * @param type The effect type to look for.
     * @return True if the player has this effect.
     */
    bool hasEffect(int type) {
        return effects_.contains(type);
    }

    /**
     * Remove effect from the list by type.
     *
     * @author Marcel Vangrootheest.
     * @param type The effect type to remove from the list.
     */
    void deleteEffect(int type);

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
     * @author Luke Queenan
     * @param type Type of effect.
     */
    void createEffect(int effectType);

    /**
     * Remove effect from the effect list.
     *
     * @author Pan K.
     * @author Marcel Vangrootheest
     * @author Luke Queenan
     * @param effect Effect to delete.
     */
    void deleteEffect(Effect*);

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
     * picks up a collectable from the ground when a player collides with it.
     *
     * @author Duncan Donaldson
     */
    void pickupCollectable(double x, double y, Unit* u);

private:
    QMap<int, Effect*> effects_;

    /** Nickname associated with this player for display purposes and chat. */
    QString nickname_;

    /** The resource (if any) that the player is currently harvesting. */
    int harvesting_;

    /** How many game ticks remaining before a resource is harvested. */ 
    int harvestCountdown_;

    /** Max harvest countdown depending on upgrade. */ 
    int harvestTime_;

    /** The resource (if any) that the player is currently carrying. */
    int resource_;

    /** If true a different Effect will be applied when colliding with NPC. */
    bool stunUpgrade_;

    /** Whether the player is moving or not. */
    bool isMoving_;

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
     * Signals player movement, this is for notifying the MainWindow for
     * scrolling purposes.
     *
     * @param pos The player's new position co-ordinate.
     *
     * @author Tom Nightingale
     */
    void signalPlayerMovement(QPointF pos);

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

    /**
     * Emitted when a player picks up a collectable from the map.
     *
     * @author Darryl Pogue
     * @param id The ID of the collectable.
     */
    void signalPickupCollectable(int id);
};

}

#endif
