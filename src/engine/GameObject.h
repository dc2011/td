#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ClsIdx.h"
#include <QPointF>
#include "../network/stream.h"

#include "PhysicsComponent.h"


class GameObject : public QObject {
  Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kGameObject;
    }

public:
    GameObject();
    virtual ~GameObject() {};

    /**
     * Reads the object state from a network stream.
     * THIS MUST BE IMPLEMENTED BY DERIVED CLASSES.
     *
     * @author Darryl Pogue
     * @param s The network stream.
     */
    virtual void networkRead(td::Stream* s) = 0;

    /**
     * Writes the object state to a network stream.
     * THIS MUST BE IMPLEMENTED BY DERIVED CLASSES.
     *
     * @author Darryl Pogue
     * @param s The network stream.
     */
    virtual void networkWrite(td::Stream* s) = 0;

    /**
     * Gets the ID of the object.
     *
     * @author Darryl Pogue
     * @return The object ID.
     */
    unsigned int getID() const {
        return iD_;
    }

    /**
     * Sets the ID of the object.
     *
     * @author Darryl Pogue
     * @param id The object ID.
     */
    void setID(unsigned int id) {
        iD_ = id;
    }
    
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

    /**
      * Overloaded < comparator for set implementation
      *
      * @author Luke Queenan
      * @returns bool
      */
    bool operator < (const GameObject &right)
    {
        return (this->iD_ < right.iD_);
    }


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
    /**
     * The unique ID for each game object
     */
    unsigned int iD_;
};
#endif
