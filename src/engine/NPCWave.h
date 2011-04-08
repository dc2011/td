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

public:
    NPCWave(QObject* parent = 0);
    NPCWave(QObject* parent, unsigned int start, unsigned int count, 
            unsigned int type);
    virtual ~NPCWave();

    void createWave();

    /**
     * Returns whether this wave has had all of its children killed.
     *
     * @author Darryl Pogue
     * @return true if there are no more children; false otherwise.
     */
    bool isDead() const {
        return children_.size() == 0;
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

public slots:
    void update();

private slots:
    /**
     * Removes a child from the set when it has been killed or destroyed.
     *
     * @author Darryl Pogue
     * @param id The id of the child that has been destroyed.
     */
    void childKilled(int);
};

}

#endif
