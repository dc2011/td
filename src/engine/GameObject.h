#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPointF>
#include "../network/stream.h"

#include "PhysicsComponent.h"


class GameObject : public QObject {
  Q_OBJECT
public:
    virtual ~GameObject() {};

    virtual void networkRead(td::Stream* s) = 0;
    virtual void networkWrite(td::Stream* s) = 0;
    
    /**
     * Returns object's position co-ords.
     * 
     * @author Tom Nightingale
     * @return QPointF.
     */
    QPointF& getPos() {
        return pos_;
    }
    
    /**
     * Sets object's position co-ords.
     * 
     * @author Tom Nightingale
     */
    void setPos(QPointF& p) {
        pos_.setX(p.x());
        pos_.setY(p.y());
        setToDirty();
        //qDebug("Pos: (%.2f, %.2f)", (float) pos_.x(), (float) pos_.y());
    }

    /**
     * Sets the object's coordinates in the game world.
     *
     * @author Darryl Pogue
     * @param x The X coordinate value.
     * @param y The Y coordinate value.
     */
    void setPos(float x, float y) {
        pos_.setX(x);
        pos_.setY(y);
        setToDirty();
    }

    /**
     * Sets the dirty_ variable to dirty
     * @author Warren Voelkl
     */
    void setToDirty() { dirty_ = true; }
    /**
     * Sets the dirty_ variable to clean
     * @author Warren Voelkl
     */
    void setToClean() { dirty_ = false; }

    /**
     * @author Warren Voelkl
     * @returns bool dirty_
     */
    bool getDirtyStatus() { return dirty_; }


public slots:
    
    /**
     * Pure virtual method that all inheriting classes need to implement.
     * This method is the starting point for responses to all events that affect the object.
     * It is a slot and thus is called when a signal is bound to it.
     * 
     * @author Tom Nightingale
     */
    virtual void update() = 0;

protected:
    QPointF pos_;
    /**
     * This variable is currently used for checking to see if the object has been drawn
     *
     */
    bool dirty_;
};
#endif
