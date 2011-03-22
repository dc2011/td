#ifndef TILEEXTENSION_H
#define TILEEXTENSION_H

#include "GameObject.h"

namespace td {

class TileExtension : public GameObject {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kTileExtension;
    }
    
    /**
     * Reads the object state from a network stream.
     * You should assign to variables directly inside this function, rather
     * than using mutator methods to change the values.
     *
     * @author Darryl Pogue, Dean Morin
     * @param s The network stream.
     */
    virtual void networkRead(td::Stream* s) {
        GameObject::networkRead(s);
    }

    /**
     * Writes the object state to a network stream.
     *
     * @author Darryl Pogue, Dean Morin
     * @param s The network stream.
     */
    virtual void networkWrite(td::Stream* s) {
        GameObject::networkWrite(s);
    }

public:
    virtual ~TileExtension() {}
};
} // end of namespace td

#endif

