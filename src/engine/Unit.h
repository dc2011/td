#ifndef UNIT_H
#define UNIT_H

#include <QPoint>

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"

class Unit : public GameObject {
public:
    virtual ~Unit();

protected:
    InputComponent* input_;
    PhysicsComponent* physics_;
};

#endif
