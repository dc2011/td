#ifndef NPC_H
#define NPC_H

#include <QVector2D>
#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "Effect.h"
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

    int getWidth(){
        return width_;
    }

    void setWidth(int width){
        width_ = width;
    }

    int getHeight(){
        return height_;
    }

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

signals:
    /**
     * signal emitted when an NPC needs to be destroyed.
     *
     * @author Duncan Donaldson
     */
    void dead(int id);

public slots:
    /**
     * Add effect to the effect list.
     *
     * @author Pan K.
     * @param type Type of effect.
     */
    void createEffect(Effect* effect);

    /**
     * Remove effect from the effect list.
     *
     * @author Pan K.
     * @param effect Effect to delete.
     */
    void deleteEffect(Effect* effect);

private:
    int health_;
    int damage_;
    int maxHealth_;
    QList<Effect> effects_;
    int height_;
    int width_;
    int type_;

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
