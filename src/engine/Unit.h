#ifndef UNIT_H
#define UNIT_H

#include <QPoint>

#include "GameObject.h"

class PhysicsComponent;
class InputComponent;
class Unit : public GameObject {
public:
    virtual ~Unit();

private:
    InputComponent * input_;
    PhysicsComponent * physics_;
};

#endif