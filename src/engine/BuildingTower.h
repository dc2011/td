#ifndef TD_BUILDINGTOWER_H
#define TD_BUILDINGTOWER_H

#include "TileExtension.h"

namespace td {

class BuildingTower : public TileExtension {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kBuildingTower;
    }

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2),
        kType           = (1 << 3),
        kWood           = (1 << 4),
        kStone          = (1 << 5),
        kBone           = (1 << 6),
        kOil            = (1 << 7)
    };


public:
    BuildingTower(QObject* parent = 0);
    virtual ~BuildingTower() {}
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
     * Checks if all the resources are there.
     *
     * @author Marcel Vangrootheest
     * @return True if all resources are at 0.
     */
    bool isDone();

    /**
     * Sets the resource wood amount.
     *
     * @author Marcel Vangrootheest, Warren Voelkl
     * @param wood The amount of wood resource needed.
     */
    void setWood(int wood);

    /**
     * Gets the amount of wood resources needed.
     * 
     * @author Marcel Vangrootheest
     * @return The resource wood amount.
     */
    int getWood() {
        return wood_;
    }


    /**
     * Sets the resource stone amount.
     *
     * @author Marcel Vangrootheest, Warren Voelkl
     * @param wood The amount of stone resource needed.
     */
    void setStone(int stone);

    /**
     * Gets the amount of stone resources needed.
     * 
     * @author Marcel Vangrootheest
     * @return The resource stone amount.
     */
    int getStone() {
        return stone_;
    }

    /**
     * Sets the resource bone amount.
     *
     * @author Marcel Vangrootheest, Warren Voelkl
     * @param wood The amount of bone resource needed.
     */
    void setBone(int bone);

    /**
     * Gets the amount of wood resources needed.
     * 
     * @author Marcel Vangrootheest
     * @return The resource wood amount.
     */
    int getBone() {
        return bone_;
    }

    /**
     * Sets the resource oil amount.
     *
     * @author Marcel Vangrootheest, Warren Voelkl
     * @param oil The amount of oil resource needed.
     */
    void setOil(int oil);

    /**
     * Gets the amount of oil resources needed.
     * 
     * @author Marcel Vangrootheest
     * @return The resource oil amount.
     */
    int getOil() {
        return oil_;
    }

private:
    /** The type of tower to be built. */
    int type_;

    /** The number of wood resources required. */
    int wood_;

    /** The number of stone resources required. */
    int stone_;

    /** The number of bone resources required. */
    int bone_;

    /** The number of oil resources required. */
    int oil_;
    /** the total amount of resources required to build structure */
    double totalResources_;
    /**
     * Checks the current building state and informs the graphics component of
     * the current image to display
     * @author Warren Voelkl
     */
    void evaluateBuildingStage();
};

} // end of namespace td

#endif

