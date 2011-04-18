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
    Tower(QObject* parent = 0);
    virtual ~Tower() {}
    virtual void initComponents();
    
    /**
     * Changes the components based on the tower type.
     *
     * @author Marcel Vangrootheest
     */
    virtual void setComponents();

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
        setDirty(kType);
    }

    /**
     * Gets the tower type
     *
     * @author Marcel Vangrootheest
     * @return The type of tower.
     */
    int getType() {
        return type_;
    }

    /**
     * Gets the level of the tower. The lowest level is level 1.
     *
     * @author Dean Morin
     * @return The level of the tower.
     */
    int getLevel() {
        return type_ & 0xF;
    }

private:
    /** The type of tower. The 4 least significant bits are the tower's level,
     *  and the next 4 are the tower type (arrow, cannon, etc.). */
    int type_;
};

} // end of namespace td

#endif

