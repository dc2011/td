#ifndef NPCINPUTCOMPONENT_H
#define NPCINPUTCOMPONENT_H

#include <QVector2D>
#include "InputComponent.h"
#include "../engine/Unit.h"

namespace td {

class NPC;

class NPCInputComponent : public InputComponent {
    Q_OBJECT
    
public:
    NPCInputComponent();
    virtual ~NPCInputComponent();
    
    void update();
    void setParent(Unit*);
    /**
     * This function calculates the force to apply to get to the destination.
     *
     * @author Marcel Vangrootheest.
     */
    void makeForce();
    /**
     * Updates the segment if NPC arrives at the current destination.
     *
     * @author Marcel Vangrootheest
     */
    void nextDestination();

private:
    /** The NPC to catch input. */
    NPC* parent_;
    /** The segment of the path NPC is currently travelling. */
    QLineF segment_;
    /** List of waypoints that the NPC must travel. */
    QList<QPointF> waypoints_;
    /** The waypoint that the NPC is currently travelling towards. */
    size_t nextDest_;
};

} /* end namespace td */

#endif // NPCINPUTCOMPONENT_H
