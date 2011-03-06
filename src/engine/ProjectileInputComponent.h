/** Input directing movement for basic projectile */
#ifndef PROJECTILEINPUTCOMPONENT
#define PROJECTILEINPUTCOMPONENT

#include "InputComponent.h"
#include "Unit.h"
class Projectile;
class ProjectileInputComponent : public InputComponent {
    Q_OBJECT

public:
    ProjectileInputComponent();
    virtual ~ProjectileInputComponent();

    /**
     * Updates the force for the projectile.
     *
     * @author Marcel Vangrootheest
     */
    void update();
    /**
     * This is needed to apply the input component to the unit defined.
     *
     * @author Marcel Vangrootheest
     * @param parent, the projectile input is applied to
     */
    void setParent(Unit* parent);
    /**
     * Makes a force that will follow the path.
     *
     * @author Marcel Vangrootheest
     */
    void makeForce();

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

public slots:

private:
    /** The projectile this component applies to. */
    Projectile* parent_;
};

#endif
