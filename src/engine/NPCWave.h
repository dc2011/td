#ifndef NPCWAVE_H
#define NPCWAVE_H

#include "NPC.h"

namespace td {

class NPCWave : public GameObject
{
    Q_OBJECT

private:
    /** A set of all the NPC objects that belong to this wave. */
    QSet<NPC*> children_;

    /** The starting time of this wave (relative to start of game). */
    unsigned int start_;

    /** The number of NPCs in this wave at the time of creation. */
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

public slots:
    void update();
};

}

#endif
