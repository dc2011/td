#ifndef TD_COLLECTABLE_H
#define TD_COLLECTABLE_H

#include "GameObject.h"

namespace td {

class Collectable : public GameObject {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kUnit;
    }

private:
    enum {
        kPosition       = (1 << 0),
        kOrientation    = (1 << 1),
        kScale          = (1 << 2)
    };

public:
    Collectable(QObject* parent = 0);
    virtual ~Collectable();

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
     * @author Duncan Donaldson
     */
    virtual void initComponents();
    
protected:
    /** Input handling logic for this Unit is contained in this component. */
    InputComponent* input_;
};

} // end namespace td

#endif

