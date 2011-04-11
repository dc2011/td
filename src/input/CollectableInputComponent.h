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
     * Applies a direction to the position.
     * This function uses path to find angle
     *
     * @author Joel Stewart , Marcel Vangrootheest
     */
    void applyDirection();

protected:
    /** The collectable this component applies to. */
    Collectable* parent_;
};

} /* end namespace td */

#endif

