#include "Tower.h"
#ifndef SERVER
#include "CDriver.h"
#endif
#include "Effect.h"
#include "../graphics/TowerGraphicsComponentTypes.h"
#include "../physics/TowerPhysicsComponentTypes.h"
#include "../util/defines.h"

namespace td {

Tower::Tower(QObject* parent) : TileExtension(parent) { }

void Tower::update() {
    if (physics_ != NULL) {
        physics_->update(this);
    }

    if (isDirty()) {
        getDriver()->update(this);
    }

    if (graphics_ != NULL) {
        graphics_->update(this);
    }
}

void Tower::networkRead(Stream* s) {
    TileExtension::networkRead(s);
    
    if (dirty_ & kType) {
        type_ = s->readInt();
    }
}

void Tower::networkWrite(Stream* s) {
    TileExtension::networkWrite(s);

    if (dirty_ & kType) {
        s->writeInt(type_);
    }
}

void Tower::initComponents() {
    switch (type_) {
        case TOWER_ARROW:
            setPhysicsComponent(new ArrowTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new ArrowTowerGraphicsComponent());
#endif
            break;
        case TOWER_CANNON:
            setPhysicsComponent(new CannonTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new CannonTowerGraphicsComponent());
#endif
            break;
        case TOWER_FLAME:
            setPhysicsComponent(new FlameTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new FlameTowerGraphicsComponent());
#endif
            break;
        case TOWER_TAR:
            setPhysicsComponent(new TarTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new TarTowerGraphicsComponent());
#endif
            break;
        case TOWER_FLAK:
            setPhysicsComponent(new FlakTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new FlakTowerGraphicsComponent());
#endif
            break;
    }
#ifndef SERVER
    connect(CDriver::instance()->getMainWindow(), SIGNAL(signalAltHeld(bool)),
                getGraphicsComponent(), SLOT(setVisibleRange(bool)));
#endif
}

void Tower::setComponents() {
    disconnect(getDriver()->getTimer(), SIGNAL(timeout()),
            this, SLOT(update()));
    switch (type_) {
    case TOWER_ARROW_2:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_ARROW_2);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_ARROW_2);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_ARROW_2);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new ArrowTowerL2GraphicsComponent());
#endif
        break;

    case TOWER_ARROW_3:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_ARROW_3);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_ARROW_3);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_ARROW_3);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new ArrowTowerL3GraphicsComponent());
#endif
        break;

    case TOWER_CANNON_2:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_CANNON_2);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_CANNON_2);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_CANNON_2);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new CannonTowerL2GraphicsComponent());
#endif
        break;

    case TOWER_CANNON_3:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_CANNON_3);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_CANNON_3);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_CANNON_3);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new CannonTowerL3GraphicsComponent());
#endif
        break;

    case TOWER_FLAME_2:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_FLAME_2);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_FLAME_2);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_FIRE_2);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new FlameTowerL2GraphicsComponent());
#endif
        break;

    case TOWER_FLAME_3:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_FLAME_3);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_FLAME_3);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_FIRE_3);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new FlameTowerL3GraphicsComponent());
#endif
        break;

    case TOWER_TAR_2:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_TAR_2);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_TAR_2);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_TAR_2);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new TarTowerL2GraphicsComponent());
#endif
        break;

    case TOWER_TAR_3:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_TAR_3);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_TAR_3);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_TAR_3);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new TarTowerL3GraphicsComponent());
#endif
        break;

    case TOWER_FLAK_2:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_FLAK_2);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_FLAK_2);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_FLAK_2);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new FlakTowerL2GraphicsComponent());
#endif
        break;

    case TOWER_FLAK_3:
        ((TowerPhysicsComponent*)physics_)
            ->setFireInterval(FIRE_INTERVAL_FLAK_3);
        ((TowerPhysicsComponent*)physics_)->setRadius(RADIUS_FLAK_3);
        ((TowerPhysicsComponent*)physics_)->setProjType(PROJ_FLAK_3);
#ifndef SERVER
        graphics_->deleteComponent();
        setGraphicsComponent(new FlakTowerL3GraphicsComponent());
#endif
        break;
    }
    connect(getDriver()->getTimer(), SIGNAL(timeout()),
            this, SLOT(update()));
}

} // end of namespace td

