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

public:
    virtual ~Resource() {}
    virtual void initComponents();
    virtual void update();

    /**
     * TODO: remove once objects are being created by the server (it's a hack).
     */
    virtual void initComponents(int resourceType);

private:
    /**
     * Set to false when the resource is initialized. On the first network read, 
     * this flag will be checked, the components will be actually initialized,
     * and the flag will be set to true. This is needed because resources 
     * require an argument (the resource type) in order to know what type of 
     * resource to become.
     */
    bool componentsInitialized_;
};
} // end of namespace td

#endif

