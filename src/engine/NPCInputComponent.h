#ifndef NPCINPUTCOMPONENT_H
#define NPCINPUTCOMPONENT_H

#include <QVector2D>
#include "InputComponent.h"
#include "Unit.h"

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

public slots:

private:
    NPC* parent_;
    QLineF segment_;
    QList<QPointF> waypoints_;
    size_t nextDest_;
};

#endif // NPCINPUTCOMPONENT_H
