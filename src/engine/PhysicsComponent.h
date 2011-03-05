#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <QObject>

class Unit;

class PhysicsComponent : public QObject {
    Q_OBJECT
public:
    virtual ~PhysicsComponent() {}

    virtual void update(Unit*) = 0;
};

#endif
