#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPoint>

//#include "InputComponent.h"
#include "PhysicsComponent.h"


class GameObject : public QObject {
  Q_OBJECT
public:
    virtual ~GameObject() {};
    
    QPoint getPos();
    void setPos(QPoint);

public slots:
    virtual void update() = 0;

private:
    QPoint pos_;
};
#endif
