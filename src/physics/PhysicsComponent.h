#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <QObject>

namespace td {

class GameObject;

class PhysicsComponent : public QObject {
    Q_OBJECT
public:
    virtual ~PhysicsComponent() {}

    virtual void update(GameObject*) = 0;
};

} /* end namespace td */

#endif
