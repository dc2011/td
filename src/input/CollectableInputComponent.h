#ifndef TD_COLLECTABLEINPUTCOMPONENT_H
#define TD_COLLECTABLEINPUTCOMPONENT_H

#include "InputComponent.h"
#include "../engine/Unit.h"

namespace td {

class Collectable;

/** Input directing movement for basic collectable */
class CollectableInputComponent : public InputComponent {
    Q_OBJECT

public:
    CollectableInputComponent();
    virtual ~CollectableInputComponent();

    /**
     * This is needed to apply the input component to the unit defined.
     *
     * @author Marcel Vangrootheest
     * @param parent, the collectable input is applied to
     */
    void setParent(Unit* parent);

    /**
     * Sets the path to points defined. Start will be set to p2, End set to p1.
     *
     * @author Marcel Vangrootheest
     * @param start, the starting position of the collectable
     * @param end, ending position of the collectable
     */
    void setPath(QPointF* start, QPointF* end);

    /**
     * Updates the force for the collectable.
     *
     * @author Marcel Vangrootheest
     */
    virtual void update();
    /**
     * Makes a force that will follow the path set.
     *
     * @author Marcel Vangrootheest
     */
    void makeForce();

    /**
     * Return true if moving to newPos is a valid move.
     *
     * @param newPos, Desired position to move to.
     *
     * @author Daniel Wright
     * @author Luke Queenan
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

protected:
    /** The collectable this component applies to. */
    Collectable* parent_;
};

} /* end namespace td */

#endif

