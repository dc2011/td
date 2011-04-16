#ifndef NPCWAVE_H
#define NPCWAVE_H

#include <QObject>
#include "NPC.h"

namespace td {

class Driver;

class NPCWave : public QObject
{
    Q_OBJECT

private:
    /** A set of all the NPC objects that belong to this wave. */
    QSet<NPC*> children_;

    /** The starting time of this wave (relative to start of game). */
    unsigned int start_;

    /** The number of NPCs to be created in this wave. */
    unsigned int count_;

    /** The type of NPCs to create for this wave. */
    unsigned int type_;

    /** The number of NPCs that have been created so far for this wave. */
    unsigned int created_;

    /** The path that the wave will follow. */
    unsigned int pathNum_;

    /** The number of gems this wave will drop. */
    unsigned int gemCount_;
    /** The density of the NPC's in this wave.
     *  value must be >0.  number is the number of game ticks between each
     *  NPC.
     */
    unsigned int density_;

public:
    NPCWave(QObject* parent = 0);
    NPCWave(QObject* parent, unsigned int start, unsigned int count, 
            unsigned int type, unsigned int path, unsigned int gems,
            unsigned int density);
    virtual ~NPCWave();

    /**
     * Begins the creation of the wave. This creates the first NPC and
     * connects to the game timer for updating.
     *
     * @author Darryl Pogue
     */
    void createWave();

    /**
     * Removes a child from the set when it has been killed or destroyed.
     *
     * @author Darryl Pogue
     * @param child The child to be removed.
     */
    void killChild(NPC* child);

    /**
     * Returns whether this wave has had all of its children killed.
     *
     * @author Darryl Pogue
     * @return true if there are no more children; false otherwise.
     */
    bool isDead() const {
        return children_.size() == 0 && count_ == created_;
    }
    unsigned int getStart(){
        return start_;
    }

private:
    /**
     * Returns the game driver to which this game object belongs.
     *
     * @author Darryl Pogue
     * @return The game driver.
     */
    Driver* getDriver() const {
        return (Driver*)this->parent();
    }

signals:
    /** Emitted when all the NPCs in the wave have been killed. */
    void waveDead();

public slots:
    /**
     * Updates the state of all NPCs in the wave, and sends that state
     * across the network.
     *
     * @author Darryl Pogue
     */
    void update();
};

}

#endif
