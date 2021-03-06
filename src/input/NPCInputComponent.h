#ifndef NPCINPUTCOMPONENT_H
#define NPCINPUTCOMPONENT_H

#include <QVector2D>
#include "InputComponent.h"
#include "../engine/Unit.h"
#include "../util/defines.h"

namespace td {

class NPC;
class CDriver;

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

    /**
      */
    void initWaypoints(int path);
private:
    /** The NPC to catch input. */
    NPC* parent_;
    /** The segment of the path NPC is currently travelling. */
    QLineF segment_;
    /** List of waypoints that the NPC must travel. */
    QList<QPointF> waypoints_;
    /** The waypoint that the NPC is currently travelling towards. */
    int nextDest_;
    /** Counter used to regulate length of time the force is applied. */
    size_t forceCounter_;

signals:
    /**
     * Deletes the unit when it reaches the players' base.
     *
     * Connected to the slot NPCDeleter() in SDriver
     *
     * @author Dean Morin
     * @param The id of the NPC to be deleted.
     */
    void deleteUnitLater(int id);
};

} /* end namespace td */

#endif // NPCINPUTCOMPONENT_H
