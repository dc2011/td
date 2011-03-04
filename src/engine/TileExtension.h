#ifndef TILEEXTENSION_H
#define TILEEXTENSION_H

#include "GameObject.h"
#include "../graphics/GraphicsComponent.h"

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

private:
    GraphicsComponent* graphics_;

public:
    TileExtension(GraphicsComponent* graphics);
    virtual ~TileExtension() {}
};
} // end of namespace td

#endif

