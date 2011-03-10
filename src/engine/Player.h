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
     * Sets the nickname associated with this player.
     *
     * @author Pan K.
     * @param type Type of effect.
     */
    void createEffect(Effect::EffectType type);

private:
    QList<Effect*> effects_;

    /**
     * A nickname associated with this player used for display purposes and chat.
     */
    QString nickname_;
};

}

#endif
