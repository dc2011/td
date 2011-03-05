#ifndef PLAYERPHYSICSCOMPONENT_H
#define PLAYERPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "Player.h"

class PlayerPhysicsComponent : public PhysicsComponent {
    Q_OBJECT

public:
    PlayerPhysicsComponent();

    /**
     * Applies a force to the velocity
     * If force is 1 or -1:
     *      Acceleration applied on direction to velocity.
     *      Deceleration is added if velocity is approaching 0.
     * If force is 0:
     *      Deceleration is applied to velocity while velocity approaches 0.
     *
     * @author Marcel Vangrootheest
     * @param Player*, pointer to the player object
     */
    void applyForce(Player*);
    /**
     * Applies a velocity to the position.
     * This function just adds the vector velocity to the point, pos
     *
     * @author Marcel Vangrootheest
     * @param Player*, pointer to the player object
     */
    void applyVelocity(Player*);
    /**
     * Applies a direction to the position.
     * This function uses velocity to find angle, pos
     *
     * @author Joel Stewart
     * @param Player*, pointer to the player object
     */
    void applyDirection(Player*);

    /**
     *
     * @author Daniel Wright
     */
    bool validateMovement(const QPointF& curPos, const QPointF& newPos);

    /**
     * Return true if pos is in unblocked half of tile.
     * Return false if pos is in blocked half of tile.
     *
     * @param pos
     * @param type
     *
     * @author Daniel Wright
     */
    bool checkSemiBlocked(QPointF pos, int type);

    /**
     * This updates the physics properties of Player.
     * Applies force to velocity, applies velocity to position.
     *
     * @author Marcel Vangrootheest
     * @param Unit*, pointer to the Unit(player object)
     */
    virtual void update(Unit*);
    
signals:
    void requestTileInfo(int row, int col, int *blockingType);

private:
    /* data */
    float accel_;
    float decel_;
    float maxVelocity_;
};

#endif
