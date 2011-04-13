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
        setGraphicsResources(RESOURCE_WOOD, wood_);
    }
    
    if (dirty_ & kStone) {
        stone_ = s->readInt();
        setGraphicsResources(RESOURCE_STONE, stone_);
    }
    
    if (dirty_ & kBone) {
        bone_ = s->readInt();
        setGraphicsResources(RESOURCE_BONE, bone_);
    }
    
    if (dirty_ & kOil) {
        oil_ = s->readInt();
        setGraphicsResources(RESOURCE_TAR, oil_);
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
            bone_   = 1;
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
    totalResources_ = wood_ + bone_ + oil_ + stone_;
#ifndef SERVER
    setGraphicsComponent(new BuildingTowerGraphicsComponent());
    getGraphicsComponent()->setBuildingResources(RESOURCE_WOOD, wood_);
    getGraphicsComponent()->setBuildingResources(RESOURCE_TAR, oil_);
    getGraphicsComponent()->setBuildingResources(RESOURCE_BONE, bone_);
    getGraphicsComponent()->setBuildingResources(RESOURCE_STONE, stone_);
#endif
}

void BuildingTower::setWood(int wood) {
    wood_ = wood;
    setDirty(kWood);
    setGraphicsResources(RESOURCE_WOOD, wood);
}

void BuildingTower::setStone(int stone) {
    stone_ = stone;
    setDirty(kStone);
    setGraphicsResources(RESOURCE_STONE, stone);
}

void BuildingTower::setOil(int oil) {
    oil_ = oil;
    setDirty(kOil);
    setGraphicsResources(RESOURCE_TAR, oil);
}

void BuildingTower::setBone(int bone) {
    bone_ = bone;
    setDirty(kBone);
    setGraphicsResources(RESOURCE_BONE, bone);
}

void BuildingTower::evaluateBuildingStage() {
    double resourcesNeeded = totalResources_ - (wood_ + oil_ + stone_ + bone_);
    if (totalResources_ == 0) {
        return;
    }
    double percentCompleted = (resourcesNeeded / totalResources_) * 100;
    if (percentCompleted < 33) {
         getGraphicsComponent()->setBuildingStage(TOWER_COMPLETE_25);
         return;
    }
    if (percentCompleted < 66) {
        getGraphicsComponent()->setBuildingStage(TOWER_COMPLETE_50);
        return;
    }
    if (percentCompleted < 100) {
        getGraphicsComponent()->setBuildingStage(TOWER_COMPLETE_75);
        return;
    }
}

void BuildingTower::setGraphicsResources(int resType, int resNum) {
    qDebug("Resource changed: %d %d", resType, resNum);
    if (getGraphicsComponent()) {
        getGraphicsComponent()->setBuildingResources(resType, resNum);
        getGraphicsComponent()->update(this);
        evaluateBuildingStage();
    }
}

} // end of namespace td


