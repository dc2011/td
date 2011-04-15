#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "../engine/Effect.h"
#include "../engine/Unit.h"
#include "../engine/Collectable.h"
#include <QSet>

namespace td {

class Player;
class CDriver;
class Map;
class Tile;
class PlayerPhysicsComponent : public PhysicsComponent {
    Q_OBJECT

public:
    PlayerPhysicsComponent();
    virtual ~PlayerPhysicsComponent() {}

    /**
     * Applies a force to the velocity
     * If force is 1 or -1:
     *      Acceleration applied on direction to velocity.
     *      Deceleration is added if velocity is approaching 0.
     * If force is 0:
     *      Deceleration is applied to velocity while velocity approaches 0.
     *
     * @author Marcel Vangrootheest
     * @param player, pointer to the player object
     */
    void applyForce(Player* player);
    /**
     * Applies a velocity to the position.
     * This function just adds the vector velocity to the point, pos
     *
     * @author Marcel Vangrootheest
     * @param player, pointer to the player object
     */
    void applyVelocity(Player* player);
    /**
     * Applies a direction to the position.
     * This function uses velocity to find angle, pos
     *
     * @author Joel Stewart
     * @param player, pointer to the player object
     */
    void applyDirection(Player* player);

    /**
     * Checks set of enemies for collisions with player.
     * If a collision is detected, adds a stun effect to the player.
     *
     * @param npcs, Set of npcs to check for collisions
     * @param player, pointer to the Unit(player object)
     *
     * @author Daniel Wright, Pan K.(add a signal)
     */
    void checkUnitCollision(QSet<Unit*> npcs, Unit* player);

    /**
     * This updates the physics properties of Player.
     * Applies force to velocity, applies velocity to position.
     *
     * @author Marcel Vangrootheest
     * @param player, pointer to the Unit(player object)
     */
    virtual void update(GameObject* player);
    /**
     * setter for max velocity of player physics component
     *
     * @author DTRAIN
     * @param maxVelocity, the new maxVelocity.
     */
    virtual void setMaxVelocity(float maxVelocity) {
        maxVelocity_ = maxVelocity;
    }
    virtual float getMaxVelocity() {
        return maxVelocity_;
    }
    
signals:
    
    /**
     * Receives x, y co-ords and returns the type of the tile occuping those 
     * co-ords.
     *
     * @param x
     * @param y
     *
     * @author Ian Lee, Tom Nightingale
     */
    void requestTileType(double x, double y, int *blockingType);

    /**
     * NPC to player collision.
     *
     * @author Pan K.
     */
    void NPCPlayerCollided(int);
    /**
     * forces a collectable to be picked up
     *
     * @author DTRAIN
     */
    void pickupCollectable(double x, double y, Unit* u);

public slots:
    /**
     * Says that it's okay to play another player/NPC collision sfx.
     *
     * @author Dean Morin
     */
    void okayToPlayCollisionSfx() {
        playCollisionSfx_ = true;
    }

private:
    /* data */
    float accel_;
    float decel_;
    float maxVelocity_;

    /** True if the player doesn't have any current collision effects applied */
    bool playCollisionSfx_;
};

} /* end namespace td */

#endif
