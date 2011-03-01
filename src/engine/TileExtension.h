#ifndef TILEEXTENSION_H
#define TILEEXTENSION_H

#include "GameObject.h"
#include "../graphics/GraphicsComponent.h"

namespace td {

class TileExtension : public GameObject {
    Q_OBJECT

private:
    GraphicsComponent* graphics_;

public:
    TileExtension(GraphicsComponent* graphics);
    virtual ~TileExtension() {}
};
} // end of namespace td

#endif

