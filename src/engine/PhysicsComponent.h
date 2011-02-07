#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <QObject>

class Player;
class PhysicsComponent : public QObject {
    Q_OBJECT
public:
    PhysicsComponent();
    virtual ~PhysicsComponent();
    
public slots:
    virtual void update(Player*) = 0;
    
};

#endif
