#ifndef PLAYER_H
#define PLAYER_H

#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "../input/PlayerInputComponent.h"
#include "CollisionComponent.h"
#include "Effect.h"
#include "../graphics/PlayerGraphicsComponent.h"
#include "../physics/PlayerPhysicsComponent.h"

namespace td {

class Player : public Unit {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kPlayer;
    }

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2),
        kNickname       = (1 << 3)
    };

public:
    Player();
    virtual ~Player() {}

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
     * @author Darryl Pogue
     */
    virtual void initComponents();

    virtual void update();

    /**
     * Gets the player's nickname.
     *
     * @author Darryl Pogue
     * @return The player's nickname.
     */
    QString getNickname() const {
        return nickname_;
    }

    /**
     * Sets the nickname associated with this player.
     *
     * @author Darryl Pogue
     * @param nick The nickname of the player.
     */
    void setNickname(QString& nick) {
        nickname_ = nick;
        setDirty(kNickname);
    }

public slots:
    /**
     * Add effect to the effect list.
     *
     * @author Pan K.
     * @param type Type of effect.
     */
    void createEffect(Effect::EffectType type);

    /**
     * Remove effect from the effect list.
     *
     * @author Pan K.
     * @param effect Effect to delete.
     */
    void deleteEffect(Effect* effect);

    /**
     * Sets the boolean that determines whether or not the player's nickname
     * should be displayed.
     *
     * @author Dean Morin
     * @param keyHeld True if the alt key is being held down.
     */
    void showName(bool keyHeld) {
        ((PlayerGraphicsComponent*) graphics_)->setShowName(keyHeld);
        update();
    }

private:
    QList<Effect*> effects_;

    /** A nickname associated with this player used for display purposes and 
     *  chat. */
    QString nickname_;

    /** The resource that this player is currently holding, if any. */
    int resource_;

signals:
    /**
     * Signals that the effect list is empty (necessary so we don't spam SFX).
     *
     * Connected to okayToPlayCollisionSfx() in PlayerPhysicsComponent.
     *
     * @author Dean Morin
     */
    void signalEmptyEffectList();
};

}

#endif
