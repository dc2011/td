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
        kType           = (1 << 3)
    };

public:
    NPC(QObject* parent = 0);
    virtual ~NPC();

    virtual void update();
    size_t getHealth();
    void setHealth(size_t);
    size_t getDamage();
    void setDamage(size_t);
    size_t getMaxHealth();
    void setMaxHealth(size_t);
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
    size_t health_;
    size_t damage_;
    size_t maxHealth_;
    QList<Effect*> effects_;
    int height_;
    int width_;
    int type_;

signals:
    /**
     * Emitted when this NPC dies to allow towers to find a new target.
     *
     * Connected to the targetDied() slot in TowerPhysicsComponent.
     *
     * @author Dean Morin
     */
    void signalNPCDied();
    
public slots:
    /**
     * Sets the boolean that determines whether or not the NPC's health bar
     * should be displayed.
     *
     * @author Dean Morin
     * @param keyHeld True if the alt key is being held down.
     */
    void showHealth(bool keyHeld) {
        ((NPCGraphicsComponent*) graphics_)->setShowHealth(keyHeld);
        update();
    }
};

} /* end namespace td */

#endif // NPC_H
