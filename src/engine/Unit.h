#ifndef UNIT_H
#define UNIT_H

#include <QVector2D>
#include <QPointF>

#include "GameObject.h"

class Unit : public GameObject {

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kUnit;
    }

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2)
    };

public:
    Unit();
    virtual ~Unit();

    /**
     * Reads the object state from a network stream.
     * You should assign to variables directly inside this function, rather
     * than using mutator methods to change the values.
     *
     * @author Darryl Pogue
     * @param s The network stream.
     */
    virtual void networkRead(td::Stream* s);

    /**
     * Writes the object state to a network stream.
     *
     * @author Darryl Pogue
     * @param s The network stream.
     */
    virtual void networkWrite(td::Stream* s);

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
     * Inheriting classes need to define a method of setting their parent
     * (owner) object.
     * 
     * @author Tom Nightingale
     */
    QVector2D getForce() {
        //qDebug("Unit::getForce: (%d, %d)", force_.x(), force_.y());
        return force_;
    }
    
    /**
     * Inheriting classes need to define a method of setting their parent
     * (owner) object.
     * 
     * @author Tom Nightingale
     */
    void setForce(QVector2D& force) {
        force_.setX(force.x());
        force_.setY(force.y());
        //qDebug("Force: %d, %d", (int) force.x(), (int) force.y());
    }

    /**
     * Gets the InputComponent for this game unit.
     *
     * @author Darryl Pogue
     * @return The object's InputComponent.
     */
    InputComponent* getInputComponent() const {
        return input_;
    }

    /**
     * Sets the InputComponent for this game unit.
     *
     * @author Darryl Pogue
     * @param input The InputComponent to assign.
     */
    void setInputComponent(InputComponent* input) {
        input_ = input;
        input_->setParent(this);
    }

protected:
    QVector2D velocity_;
    QVector2D force_;

    /**
     * All input handling logic for this Unit is contained in this component.
     */
    InputComponent* input_;
};

#endif
