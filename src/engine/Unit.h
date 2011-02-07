#ifndef UNIT_H
#define UNIT_H

#include <QVector2D>
#include <QPoint>

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"

class Unit : public GameObject {
public:
    virtual ~Unit();

    QVector2D& GetVelocity();
    void SetVelocity(QVector2D&);

    QVector2D& GetAccel();
    void SetAccel(QVector2D&);

    QPoint& GetPos();
    void SetPos(QPoint&);

    int GetOrientation();
    void SetOrientation(int);

    float GetScale();
    void SetScale(float);

private:
    QVector2D velocity_;
    QVector2D accel_;
    QPoint pos_;
    int orientation_;
    float scale_;

protected:
    InputComponent* input_;
    PhysicsComponent* physics_;
};

#endif
