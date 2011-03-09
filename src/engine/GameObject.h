#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ClsIdx.h"
#include <QPointF>
#include "../input/InputComponent.h"
#include "../physics/PhysicsComponent.h"
#include "../graphics/GraphicsComponent.h"
#include "../network/stream.h"

namespace td {

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

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2)
    };

protected:
    GameObject(); /* Protected to enforce "abstract" class */

public:
    virtual ~GameObject();

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
     * This function will do any component initialization whenever
     * a gameobject is created.
     *
     * PLEASE IMPLEMENT THIS FOR GREAT JUSTICE.
     *
     * @author Duncan Donaldson
     */
    virtual void initComponents(){}
protected:
    /**
     * Sets the dirty bit for the specified field.
     *
     * @author Darryl Pogue
     * @param field The bit index of the field to be marked.
     */
    void setDirty(unsigned int field) {
        dirty_ |= field;
    }

    /**
     * Resets the dirty bit for the specified field.
     *
     * @author Darryl Pogue
     * @param field The bit index of the field to be unmarked.
     */
    void unsetDirty(unsigned int field) {
        dirty_ &= ~(field);
    }

public:
    /**
     * Returns whether this object has fields that have been marked as dirty.
     *
     * @author Darryl Pogue
     * @author Warren Voelkl
     * @return true if the object is dirty, false otherwise.
     */
    bool isDirty() {
        return (dirty_ != 0);
    }

    /**
     * Resets the dirty state for this object.
     *
     * @author Darryl Pogue
     */
    void resetDirty() {
        dirty_ = 0;
    }

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
     * Sets the object's coordinates in the game world. This should be the
     * center of the object.
     * 
     * @author Tom Nightingale
     * @param p The coordinates of the center of the object.
     */
    void setPos(QPointF& p) {
        pos_.setX(p.x());
        pos_.setY(p.y());
        setDirty(kPosition);
        //qDebug("Pos: (%.2f, %.2f)", (float) pos_.x(), (float) pos_.y());
    }

    /**
     * Sets the object's coordinates in the game world. This should be the
     * center of the object.
     *
     * @author Darryl Pogue
     * @param x The X coordinate value.
     * @param y The Y coordinate value.
     */
    void setPos(float x, float y) {
        pos_.setX(x);
        pos_.setY(y);
        setDirty(kPosition);
    }
    
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

    /**
     * Get the direction of the GameObject, where 0 degrees is east.
     *
     * @author Dean Morin
     * @return The orientation of the GameObject in degrees.
     */
    int getOrientation() {
        return orientation_;
    }

    /**
     * Set the direction of the GameObject, where 0 degrees is east.
     *
     * @author Dean Morin
     * @param orient The new orientation of the GameObject.
     */
    void setOrientation(int orient) {
        orientation_ = orient;
        setDirty(kOrientation);
    }

    /**
     * Get the scale of the GameObject, where 1 is unscaled.
     *
     * @author Dean Morin
     * @return The scale of the GameObject.
     */
    float getScale() {
        return scale_;
    }

    /**
     * Set the scale of the GameObject, where 1 is unscaled.
     *
     * @author Dean Morin
     * @param scale The new scale of the object.
     */
    void setScale(float scale) {
        scale_ = scale;
        setDirty(kScale);
    }

    /**
     * Get a pointer to this object's graphics component.
     *
     * @author Darryl Pogue
     * @return This object's graphics component;
     */
    GraphicsComponent* getGraphicsComponent() const {
        return graphics_;
    }
    
    /**
     * Set the graphics component for this object.
     *
     * @author Darryl Pogue
     * @param graphics The GraphicsComponent to use for rendering.
     */
    void setGraphicsComponent(GraphicsComponent* graphics) {
        graphics_ = graphics;
    }

    /**
     * Get a pointer to this object's physics component. Please note that not
     * all GameObjects will have a physics component.
     *
     * @author Darryl Pogue
     * @return This object's physics component;
     */
    PhysicsComponent* getPhysicsComponent() const {
        if (physics_ == NULL) {
            qDebug("GameObject::getPhysicsComponent(); Getting null pointer");
        }
        return physics_;
    }

    /**
     * Set the physics component for this object. Please note that not all
     * GameObjects will have a physics component.
     *
     * @author Darryl Pogue
     * @param physics The PhysicsComponent to be used for this object.
     */
    void setPhysicsComponent(PhysicsComponent* physics) {
        physics_ = physics;
    }
    
public slots:
    /**
     * Pure virtual method that all inheriting classes need to implement.
     * This method is the starting point for responses to all events that 
     * affect the object.
     *
     * It is a slot and thus is called when a signal is bound to it.
     * 
     * @author Tom Nightingale
     */
    virtual void update() = 0;

protected:
    /**
     * This keeps track of which values of the object have been updated
     * internally but not externally displayed.
     */
    unsigned int dirty_;

    /**
     * The unique ID for each game object.
     */
    unsigned int iD_;

    /**
     * The position of the GameObject in the world.
     */
    QPointF pos_;
   
    /**
     * The direction of the GameObject, where 0 degrees is east.
     */
    int orientation_;

    /**
     * The scale of the GameObject, where 1 is unscaled.
     */
    float scale_;

    /**
     * All rendering logic for this GameObject is contained in this component.
     */
    GraphicsComponent* graphics_;
    
    /**
     * All physics logic for this GameObject is contained in this component.
     * Not all GameObjects will have a physics component.
     */
    PhysicsComponent* physics_;
};

} /* end namespace td */

#endif

