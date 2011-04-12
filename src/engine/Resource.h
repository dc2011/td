#ifndef TD_RESOURCE_H
#define TD_RESOURCE_H

#include "TileExtension.h"

namespace td {

class Effect;

class Resource : public TileExtension {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kResource;
    }

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2),
        kType           = (1 << 3),
        kRemaining      = (1 << 4)
    };

public:
    Resource(QObject* parent = 0);
    virtual ~Resource() {}
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
     * Sets the resource type (wood, stone, bone, or tar).
     *
     * @author Darryl Pogue, Dean Morin
     * @param The type of resource.
     */
    void setType(int type) {
        type_ = type;
        setDirty(kType);
    }

private:
    int type_;
    int remaining_;
};

} // end of namespace td

#endif

