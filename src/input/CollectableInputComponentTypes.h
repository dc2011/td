#ifndef TD_COLLECTABLEINPUTCOMPONENTTYPES_H
#define TD_COLLECTABLEINPUTCOMPONENTTYPES_H

#include "CollectableInputComponent.h"

namespace td {

class ResourceCollectableInputComponent : public CollectableInputComponent {
    Q_OBJECT

public:
    ResourceCollectableInputComponent() : CollectableInputComponent() {}
    virtual ~ResourceCollectableInputComponent() {}
    
    virtual void update();
    /**
     * Makes a force that will follow the path.
     *
     * @author Marcel Vangrootheest
     */
    void makeForce();
};

class GemCollectableInputComponent : public CollectableInputComponent {
    Q_OBJECT

public:
    GemCollectableInputComponent() : CollectableInputComponent() {}
    virtual ~GemCollectableInputComponent() {}

    /**
     * Updates the force for the collectable.
     *
     * @author Marcel Vangrootheest
     */
    virtual void update();
    /**
     * Makes a force that will follow the path.
     *
     * @author Marcel Vangrootheest
     */
    void makeForce();
};

} /* end namespace td */

#endif


