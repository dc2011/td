#include "PhysicsComponent.h"
#include "PlayerPhysicsComponent.h"
#include "Player.h"

class PlayerPhysicsComponent : public PhysicsComponent {
public:
    PlayerPhysicsComponent();
    virtual ~PlayerPhysicsComponent() {};
    
    virtual void Update(Player&);
    
private:
    /* data */
};