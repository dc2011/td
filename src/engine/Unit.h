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

    QVector2D GetForce() {
        return force_;
    }
    
    void SetForce(QVector2D& force) {
        force_.setX(force.x());
        force_.setY(force.y());
        qDebug("Force: %d, %d", (int) force.x(), (int) force.y());
    }

    QPoint& GetPos() {
        return pos_;
    }
    
    void SetPos(QPoint& pos) {
        pos_.setX(pos.x());
        pos_.setY(pos.y());
        qDebug("Pos: (%d, %d)", (int) pos_.x(), (int) pos_.y());
    }

    int GetOrientation();
    void SetOrientation(int);

    float GetScale();
    void SetScale(float);

private:
    QVector2D velocity_;
    QVector2D force_;
    QPoint pos_;
    int orientation_;
    float scale_;

protected:
    InputComponent* input_;
    PhysicsComponent* physics_;
};

#endif
