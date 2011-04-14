#include "BuildingTower.h"
#include "Driver.h"
#include "../graphics/BuildingTowerGraphicsComponent.h"
#include "../util/defines.h"
#include <QDebug>

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
            wood_   = COST_ARROW_WOOD;
            bone_   = COST_ARROW_BONE;
            stone_  = COST_ARROW_STONE;
            oil_    = COST_ARROW_OIL;
            break;
        case TOWER_CANNON:
            wood_   = COST_CANNON_WOOD;
            bone_   = COST_CANNON_BONE;
            stone_  = COST_CANNON_STONE;
            oil_    = COST_CANNON_OIL;
            break;
        case TOWER_FLAME:
            wood_   = COST_FLAME_WOOD;
            bone_   = COST_FLAME_BONE;
            stone_  = COST_FLAME_STONE;
            oil_    = COST_FLAME_OIL;
            break;
        case TOWER_TAR:
            wood_   = COST_TAR_WOOD;
            bone_   = COST_TAR_BONE;
            stone_  = COST_TAR_STONE;
            oil_    = COST_TAR_OIL;
            break;
        case TOWER_FLAK:
            wood_   = COST_FLAK_WOOD;
            bone_   = COST_FLAK_BONE;
            stone_  = COST_FLAK_STONE;
            oil_    = COST_FLAK_OIL;
            break;
    }
    totalResources_ = wood_ + bone_ + oil_ + stone_;
#ifndef SERVER
    setGraphicsComponent(new BuildingTowerGraphicsComponent());
#endif
}

void BuildingTower::setWood(int wood) {
    wood_ = wood;
    setDirty(kWood);
}

void BuildingTower::setStone(int stone) {
    stone_ = stone;
    setDirty(kStone);
}

void BuildingTower::setOil(int oil) {
    oil_ = oil;
    setDirty(kOil);
}

void BuildingTower::setBone(int bone) {
    bone_ = bone;
    setDirty(kBone);
}

int BuildingTower::evaluateBuildingStage() {
    double resourcesNeeded = totalResources_ - (wood_ + oil_ + stone_ + bone_);
    if (totalResources_ == 0) {
        return TOWER_COMPLETE_75;
    }
    double percentCompleted = (resourcesNeeded / totalResources_) * 100;
    if (percentCompleted < 33) {
         return TOWER_COMPLETE_25;
    }
    if (percentCompleted < 66) {
        return TOWER_COMPLETE_50;
    }
    if (percentCompleted < 100) {
        return TOWER_COMPLETE_75;
    }
}

} // end of namespace td


