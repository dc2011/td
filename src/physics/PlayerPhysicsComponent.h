#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "Bounds.h"
#include "../engine/Effect.h"
#include <set>

namespace td {

class Player;

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
     * Return true if moving to newPos is a valid move.
     *
     * @param newPos, Desired position to move to.
     *
     * @author Daniel Wright
     */
    bool validateMovement(const QPointF& newPos);

    /**
     * Return true if pos is in unblocked half of tile.
     * Return false if pos is in blocked half of tile.
     *
     * @param pos, Position to be checked
     * @param type, Blocking type of tile
     *
     * @author Daniel Wright
     */
    bool checkSemiBlocked(QPointF pos, int type);

    /**
     * Checks set of enemies for collisions with player.
     * If a collision is detected, adds a stun effect to the player.
     *
     * @param npcs, Set of npcs to check for collisions
     *
     * @author Daniel Wright, Pan K.(add a signal)
     */
    void checkNPCCollision(std::set<Unit*> npcs);

    /**
     * This updates the physics properties of Player.
     * Applies force to velocity, applies velocity to position.
     *
     * @author Marcel Vangrootheest
     * @param player, pointer to the Unit(player object)
     */
    virtual void update(Unit* player);
    
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
    void NPCPlayerCollided(Effect::EffectType);


private:
    /* data */
    float accel_;
    float decel_;
    float maxVelocity_;

    td::BoxBounds collider_;
};

} /* end namespace td */

#endif
