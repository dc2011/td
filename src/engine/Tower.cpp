#include "Tower.h"

namespace td {

Tower::Tower(PhysicsComponent* physics, GraphicsComponent* graphics) 
        : TileExtension(graphics), physics_(physics) {
}

} // end of namespace td

