#ifndef TD_TOWER_H
#define TD_TOWER_H

#include "TileExtension.h"

namespace td {

class Effect;

class Tower : public TileExtension {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kTower;
    }

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2),
        kType           = (1 << 3)
    };

public:
    virtual ~Tower() {}
    virtual void initComponents();
    
    /**
     * Reads the object state from a network stream.
     * You should assign to variables directly inside this function, rather
     * than using mutator methods to change the values.
     *
     * @author Darryl Pogue, Dean Morin
     * @param s The network stream.
     */
    virtual void networkRead(td::Stream* s);

    /**
     * Writes the object state to a network stream.
     *
     * @author Darryl Pogue, Dean Morin
     * @param s The network stream.
     */
    virtual void networkWrite(td::Stream* s);
    
    virtual void update();

    /**
     * Sets the tower type (arrow, cannon, tar, flame, or flak).
     *
     * @author Darryl Pogue
     * @param The type of tower.
     */
    void setType(int type) {
        type_ = type;
    }

private:
    int type_;
};

} // end of namespace td

#endif

