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

    QPoint& getPos() {
        return pos_;
    }
    
    void setPos(QPoint& pos) {
        pos_.setX(pos.x());
        pos_.setY(pos.y());
        qDebug("Pos: (%d, %d)", (int) pos_.x(), (int) pos_.y());
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
};

#endif
