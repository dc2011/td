#include "Tower.h"

td::Tower::Tower(PhysicsComponent* physics, GraphicsComponent* graphics) 
        : TileExtension(graphics), physics_(physics) {
} 

