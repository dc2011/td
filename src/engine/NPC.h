#ifndef NPC_H
#define NPC_H

#include <QVector2D>
#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "Effect.h"
#include "EffectTypes.h"
#include "../input/NPCInputComponentTypes.h"
#include "../physics/NPCPhysicsComponentTypes.h"
#include "../graphics/NPCGraphicsComponentTypes.h"

namespace td {

class NPCWave;

class NPC : public Unit {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kNPC;
    }

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2),
        kType           = (1 << 3),
        kHealth         = (1 << 4)
    };

public:
    NPC(QObject* parent = 0);
    virtual ~NPC();

    virtual void update();
    int getHealth();
    /**
     * Checks to see if the health is a positive value now before displaying the
     * health bar.
     *
     * @author Luke Queenan
     */
    void setHealth(int);
    int getDamage();
    void setDamage(int);
    int getMaxHealth();
    void setMaxHealth(int);
    /**
     * if an NPC's health reaches 0,
     * emit a signal that will have the NPC destroyed.
     *
     * @author Duncan Donaldson
     */
    void isDead();

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
     * initializes the NPCs components.
     *
     * @author Duncan Donaldson
     */
    virtual void initComponents();
	
	/**
	  * Returns the width of the NPC's sprite.
	  * 
	  * @author Daniel Wright
	  * @return Width of the NPC sprite.
	  */
    int getWidth(){
        return width_;
    }
	
	/**
	  * Sets the width value for the NPC to the supplied value.
	  *
	  * @author Daniel Wright
	  * @param width The new width of the NPC
	  */
    void setWidth(int width){
        width_ = width;
    }
	
	/**
	  * Returns the height of the NPC's sprite.
	  * 
	  * @author Daniel Wright
	  * @return Height of the NPC sprite.
	  */
    int getHeight(){
        return height_;
    }
	
	/**
	  * Sets the height value for the NPC to the supplied value.
	  *
	  * @author Daniel Wright
	  * @param height The new height of the NPC
	  */
    void setHeight(int height){
        height_ = height;
    }

    /**
     * Sets the NPC type (Normal, Slow, Fast, Flying, or Boss).
     *
     * @author Marcel Vangrootheest.
     * @param type NPC type
     */
    void setType(int type) {
        type_ = type;
        setDirty(kType);
    }
    int getType() {
        return type_;
    }

    /**
     * Returns the wave that owns the NPC.
     *
     * @author Darryl Pogue
     * @return The NPCWave to which the NPC belongs.
     */
    NPCWave* getWave() const {
        return wave_;
    }

    /**
     * Sets the wave that owns the NPC.
     *
     * @author Darryl Pogue
     * @param wave The NPCWave to which the NPC belongs.
     */
    void setWave(NPCWave* wave) {
        wave_ = wave;
    }

    /**
     * Makes a random vector for the collectable drop.
     *
     * @author Marcel Vangrootheest
     * @return A random vector
     */
    QVector2D getRandomVector();

    /**
     * Sets the gem holding amount. Should be 0 or 1.
     *
     * @author Marcel Vangrootheest
     * @param gem The number of gems you want NPC to hold.
     */
    void setGem(int gem) {
        gem_ = gem;
    }

    int getGem() {
        return gem_;
    }

signals:
    /**
     * signal emitted when an NPC needs to be destroyed.
     *
     * @author Duncan Donaldson
     */
    void dead(int id);

    /**
     * Stops applying an effect.
     * Used when replacing an effect in a list.
     * Connected to effectStop() in Effect.
     *
     * @author Marcel Vangrootheest
     * @param type The type of Effect.
     */
    void stopEffect(uint type);

    /**
     * Emmitted when the player drops the resource that they are carrying.
     *
     * Connected to requestCollectable() in the driver.
     *
     * @author Dean Morin
     * @param type The resource type.
     * @param pos The player's coords when he drops the resource.
     * @param velocity The player's velocity when he drops the resource.
     */
    void signalDropResource(int type, QPointF pos, QVector2D velocity);

public slots:
    /**
     * Add effect to the effect list.
     * Replaces effect if type already exists in list.
     *
     * @author Pan K.
     * @author Marcel Vangrootheest
     * @author Luke Queennan
     * @param type Type of effect.
     */
    void createEffect(int effectType);

    /**
     * Remove effect from the effect list.
     *
     * @author Pan K.
     * @author Marcel Vangrootheest
     * @author Duncan Donaldson
     * @param effect Effect to delete.
     */
    void deleteEffect(Effect* effect);

private:
    int health_;
    int damage_;
    int maxHealth_;
    QMap<int, Effect*> effects_;
    /** Height of the NPC sprite. */
	int height_;
	/** Width of the NPC sprite. */
    int width_;
    int type_;
    int gem_;

    /** The wave to which this NPC belongs. */
    NPCWave* wave_;

signals:
    /**
     * Emitted when this NPC dies to allow towers to find a new target.
     *
     * Connected to the targetDied() slot in TowerPhysicsComponent.
     *
     * @author Dean Morin
     */
    void signalNPCDied();
};

} /* end namespace td */

#endif // NPC_H
