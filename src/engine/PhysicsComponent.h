#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <QObject>

class Unit;

class PhysicsComponent : public QObject {
    Q_OBJECT
public:
    PhysicsComponent();
    virtual ~PhysicsComponent();
    
public slots:
    virtual void update(Unit*) = 0;
};

#endif
