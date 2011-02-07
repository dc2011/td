#ifndef UNIT_H
#define UNIT_H

#include <QVector2D>
#include <QPoint>

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"

class Unit : public GameObject {
public:
    virtual ~Unit();

    QVector2D& getVelocity();
    void setVelocity(QVector2D&);

    QVector2D getForce() {
        return force_;
    }
    
    void setForce(QVector2D& force) {
        force_.setX(force.x());
        force_.setY(force.y());
        qDebug("Force: %d, %d", (int) force.x(), (int) force.y());
    }

    int getOrientation();
    void setOrientation(int);

    float getScale();
    void setScale(float);

private:
    QVector2D velocity_;
    QVector2D force_;
    QPoint pos_;
    int orientation_;
    float scale_;

protected:
    InputComponent* input_;
    PhysicsComponent* physics_;
    GraphicsComponent* graphics_;
};

#endif
