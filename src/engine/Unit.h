#ifndef UNIT_H
#define UNIT_H

#include <QVector2D>
#include <QPointF>

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"

class Unit : public GameObject {
public:
    virtual ~Unit();

    /**
     * Inheriting classes need to define a method of setting their parent (owner) object.
     * 
     * @author Tom Nightingale
     */
    QVector2D& getVelocity();

    /**
     * Inheriting classes need to define a method of setting their parent (owner) object.
     * 
     * @author Tom Nightingale
     */
    void setVelocity(QVector2D&);

    /**
     * Inheriting classes need to define a method of setting their parent (owner) object.
     * 
     * @author Tom Nightingale
     */
    QVector2D getForce() {
        //qDebug("Unit::getForce: (%d, %d)", force_.x(), force_.y());
        return force_;
    }
    
    /**
     * Inheriting classes need to define a method of setting their parent (owner) object.
     * 
     * @author Tom Nightingale
     */
    void setForce(QVector2D& force) {
        force_.setX(force.x());
        force_.setY(force.y());
        //qDebug("Force: %d, %d", (int) force.x(), (int) force.y());
    }

    int getOrientation();
    void setOrientation(int);

    float getScale();
    void setScale(float);

protected:
    QVector2D velocity_;
    QVector2D force_;
    int orientation_;
    float scale_;

    InputComponent* input_;
    PhysicsComponent* physics_;
    GraphicsComponent* graphics_;
};

#endif
