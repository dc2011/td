#include "BuildingTower.h"
#include "Driver.h"
#include "../graphics/BuildingTowerGraphicsComponent.h"
#include "../util/defines.h"

namespace td {

BuildingTower::BuildingTower(QObject* parent) : TileExtension(parent) {
    wood_ = 0;
    stone_ = 0;
    bone_ = 0;
    oil_ = 0;
}

void BuildingTower::update() {
    if (isDirty()) {
        getDriver()->update(this);
    }

    if (graphics_ != NULL) {
        graphics_->update(this);
    }
}

void BuildingTower::networkRead(Stream* s) {
    TileExtension::networkRead(s);
    
    if (dirty_ & kType) {
        type_ = s->readInt();
    }
    
    if (dirty_ & kWood) {
        wood_ = s->readInt();
    }
    
    if (dirty_ & kStone) {
        stone_ = s->readInt();
    }
    
    if (dirty_ & kBone) {
        bone_ = s->readInt();
    }
    
    if (dirty_ & kOil) {
        oil_ = s->readInt();
    }
}

void BuildingTower::networkWrite(Stream* s) {
    TileExtension::networkWrite(s);

    if (dirty_ & kType) {
        s->writeInt(type_);
    }

    if (dirty_ & kWood) {
        s->writeInt(wood_);
    }

    if (dirty_ & kStone) {
        s->writeInt(stone_);
    }

    if (dirty_ & kBone) {
        s->writeInt(bone_);
    }

    if (dirty_ & kOil) {
        s->writeInt(oil_);
    }
}

bool BuildingTower::isDone() {
    return (!wood_ && !stone_ && !bone_ && !oil_);
}

void BuildingTower::initComponents() {
    switch (type_) {
        case TOWER_ARROW:
            wood_   = 1;
            break;
        case TOWER_CANNON:
            stone_  = 1;
            break;
        case TOWER_FLAME:
            bone_   = 2;
            break;
        case TOWER_TAR:
            oil_  = 2;
            break;
        case TOWER_FLAK:
            wood_   = 1;
            bone_   = 1;
            break;
    }
#ifndef SERVER
    setGraphicsComponent(new BuildingTowerGraphicsComponent());
#endif
}

} // end of namespace td


