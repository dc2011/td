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

    void update();
    void setParent(Unit*);
    /**
     *
     * @author Marcel Vangrootheest
     */
    void makeForce();

    /**
     *
     * @author Marcel Vangrootheest
     */
    void setPath(QPointF start, QPointF end);

public slots:

private:
};

#endif
