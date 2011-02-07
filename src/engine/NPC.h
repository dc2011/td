#ifndef NPC_H
#define NPC_H

#include "Unit.h"

class NPC : public Unit {
    Q_OBJECT
public:
    NPC(PhysicsComponent* physics);

    virtual void Update();
    size_t GetHealth();
    void SetHealth(size_t);
    size_t GetDamage();
    void SetDamage(size_t);

private:
    size_t health_;
    size_t damage_;
};

#endif // NPC_H
