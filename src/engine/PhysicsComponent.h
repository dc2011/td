#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

class Player;
class PhysicsComponent : public QObject {
    Q_OBJECT
public:
    PhysicsComponent();
    ~PhysicsComponent();
    
    void Accelerate(Player*);
    void Decelerate(Player*);
    
public slots:
    virtual void Update(Player*) = 0;
    
private:
    const size_t acceleration_;
    const size_t deceleration_;
};

#endif