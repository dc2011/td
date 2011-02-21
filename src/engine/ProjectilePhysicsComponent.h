#ifndef PROJECTILEPHYSICSCOMPONENT_H
#define PROJECTILEPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "Projectile.h"
class ProjectilePhysicsComponent : public PhysicsComponent {
public:
    ProjectilePhysicsComponent();
    virtual ~ProjectilePhysicsComponent();
    void applyVelocity(Projectile*);
    void setAngle(Projectile*);
    void makePath(Projectile*);

public slots:
    virtual void update(Unit*);

private:
    float maxVelocity_;
    QLineF path;
};

#endif
