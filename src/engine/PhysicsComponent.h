#include "PhysicsComponent.h"
#include "Player.h"

class PhysicsComponent {
public:
    PhysicsComponent();
    ~PhysicsComponent() {}
    
    virtual void Update(Player&) = 0;
    void Accelerate(Player&);
    void Decelerate(Player&);
    
private:
    const size_t acceleration_;
    const size_t deceleration_;
};