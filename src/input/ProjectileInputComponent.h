#ifndef PROJECTILEINPUTCOMPONENT
#define PROJECTILEINPUTCOMPONENT

#include "InputComponent.h"
#include "../engine/Unit.h"

namespace td {

class Projectile;

/** Input directing movement for basic projectile */
class ProjectileInputComponent : public InputComponent {
    Q_OBJECT

public:
    ProjectileInputComponent();
    virtual ~ProjectileInputComponent();

    /**
     * This is needed to apply the input component to the unit defined.
     *
     * @author Marcel Vangrootheest
     * @param parent, the projectile input is applied to
     */
    void setParent(Unit* parent);

    /**
     * Sets the path to points defined. Start will be set to p2, End set to p1.
     *
     * @author Marcel Vangrootheest
     * @param start, the starting position of the projectile
     * @param end, ending position of the projectile
     */
    void setPath(QPointF* start, QPointF* end);

    /**
     * Applies a direction to the position.
     * This function uses path to find angle
     *
     * @author Joel Stewart , Marcel Vangrootheest
     */
    void applyDirection();

    /**
     * Makes a force that will follow the path.
     *
     * @author Marcel Vangrootheest
     */
    virtual void makeForce();
    /**
     * Checks for collision between projectile and npcs
     * and applies effects to hit npcs.
     *
     * @author Daniel Wright
     * @param npcs, set of npcs to check collision with
     */
    virtual void checkNPCCollision(QSet<Unit*> npcs){}

signals:
    /**
     * Deletes the projectile.
     *
     * Connected to deleteObjLocal() in CDriver.
     *
     * @author Dean Morin
     */
    void deleteProjectileLater(int id);

protected:
    /** The projectile this component applies to. */
    Projectile* parent_;
};

} /* end namespace td */

#endif
