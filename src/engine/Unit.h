#include <QPoint>

#include "GameObject.h"


class Unit : public GameObject {
public:
    virtual ~Unit() {};

private:
    InputComponent input_;
    PhysicsComponent physics_;
};