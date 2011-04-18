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
        case TOWER_ARROW_1:
            setPhysicsComponent(new ArrowTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new ArrowTowerGraphicsComponent());
#endif
            type_ = TOWER_ARROW_1;
            break;
        case TOWER_CANNON_1:
            setPhysicsComponent(new CannonTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new CannonTowerGraphicsComponent());
#endif
            type_ = TOWER_CANNON_1;
            break;
        case TOWER_FLAME_1:
            setPhysicsComponent(new FlameTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new FlameTowerGraphicsComponent());
#endif
            type_ = TOWER_FLAME_1;
            break;
        case TOWER_TAR_1:
            setPhysicsComponent(new TarTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new TarTowerGraphicsComponent());
#endif
            type_ = TOWER_TAR_1;
            break;
        case TOWER_FLAK_1:
            setPhysicsComponent(new FlakTowerPhysicsComponent(this));
#ifndef SERVER
            setGraphicsComponent(new FlakTowerGraphicsComponent());
#endif
            type_ = TOWER_FLAK_1;
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
#ifndef SERVER
    graphics_->deleteComponent();
#endif
    int type = type_ >> 4;
    if (type == 0) {
        switch (type_) {
            case TOWER_ARROW_2:
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_ARROW_2);
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_ARROW_2);
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_ARROW_2);
#ifndef SERVER
                setGraphicsComponent(new ArrowTowerGraphicsComponent());
#endif
                break;

            case TOWER_ARROW_3:
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_ARROW_3);
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_ARROW_3);
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_ARROW_3);
#ifndef SERVER
                setGraphicsComponent(new ArrowTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_ARROW_4:
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_ARROW_4);
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_ARROW_4);
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_ARROW_4);
#ifndef SERVER
                setGraphicsComponent(new ArrowTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_ARROW_5:
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_ARROW_5);
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_ARROW_5);
                ((ArrowTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_ARROW_5);
#ifndef SERVER
                setGraphicsComponent(new ArrowTowerL3GraphicsComponent());
#endif
                break;
        }
    } else if (type == 1) {
        switch (type_) {
            case TOWER_CANNON_2:
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_CANNON_2);
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_CANNON_2);
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_CANNON_2);
#ifndef SERVER
                setGraphicsComponent(new CannonTowerGraphicsComponent());
#endif
                break;
            case TOWER_CANNON_3:
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_CANNON_3);
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_CANNON_3);
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_CANNON_3);
#ifndef SERVER
                setGraphicsComponent(new CannonTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_CANNON_4:
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_CANNON_4);
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_CANNON_4);
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_CANNON_4);
#ifndef SERVER
                setGraphicsComponent(new CannonTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_CANNON_5:
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_CANNON_5);
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_CANNON_5);
                ((CannonTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_CANNON_5);
#ifndef SERVER
                setGraphicsComponent(new CannonTowerL3GraphicsComponent());
#endif
                break;
        }
    } else if (type == 2) {
        switch (type_) {
            case TOWER_FLAME_2:
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_FLAME_2);
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_FLAME_2);
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_FIRE_2);
#ifndef SERVER
                setGraphicsComponent(new FlameTowerGraphicsComponent());
#endif
                break;
            case TOWER_FLAME_3:
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_FLAME_3);
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_FLAME_3);
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_FIRE_3);
#ifndef SERVER
                setGraphicsComponent(new FlameTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_FLAME_4:
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_FLAME_4);
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_FLAME_4);
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_FIRE_4);
#ifndef SERVER
                setGraphicsComponent(new FlameTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_FLAME_5:
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_FLAME_5);
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_FLAME_5);
                ((FlameTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_FIRE_5);
#ifndef SERVER
                setGraphicsComponent(new FlameTowerL3GraphicsComponent());
#endif
                break;
        }
    } else if (type == 3) {
        switch (type_) {
            case TOWER_TAR_2:
                ((TarTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_TAR_2);
                ((TarTowerPhysicsComponent*)physics_)->setRadius(RADIUS_TAR_2);
                ((TarTowerPhysicsComponent*)physics_)->setProjType(PROJ_TAR_2);
#ifndef SERVER
                setGraphicsComponent(new TarTowerGraphicsComponent());
#endif
                break;
            case TOWER_TAR_3:
                ((TarTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_TAR_3);
                ((TarTowerPhysicsComponent*)physics_)->setRadius(RADIUS_TAR_3);
                ((TarTowerPhysicsComponent*)physics_)->setProjType(PROJ_TAR_3);
#ifndef SERVER
                setGraphicsComponent(new TarTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_TAR_4:
                ((TarTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_TAR_4);
                ((TarTowerPhysicsComponent*)physics_)->setRadius(RADIUS_TAR_4);
                ((TarTowerPhysicsComponent*)physics_)->setProjType(PROJ_TAR_4);
#ifndef SERVER
                setGraphicsComponent(new TarTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_TAR_5:
                ((TarTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_TAR_5);
                ((TarTowerPhysicsComponent*)physics_)->setRadius(RADIUS_TAR_5);
                ((TarTowerPhysicsComponent*)physics_)->setProjType(PROJ_TAR_5);
#ifndef SERVER
                setGraphicsComponent(new TarTowerL3GraphicsComponent());
#endif
                break;
        }
    } else if (type == 4) {
        switch (type_) {
            case TOWER_FLAK_2:
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_FLAK_2);
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_FLAK_2);
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_FLAK_2);
#ifndef SERVER
                setGraphicsComponent(new FlakTowerGraphicsComponent());
#endif
                break;
            case TOWER_FLAK_3:
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_FLAK_3);
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_FLAK_3);
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_FLAK_3);
#ifndef SERVER
                setGraphicsComponent(new FlakTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_FLAK_4:
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_FLAK_4);
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_FLAK_4);
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_FLAK_4);
#ifndef SERVER
                setGraphicsComponent(new FlakTowerL2GraphicsComponent());
#endif
                break;
            case TOWER_FLAK_5:
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setFireInterval(FIRE_INTERVAL_FLAK_5);
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setRadius(RADIUS_FLAK_5);
                ((FlakTowerPhysicsComponent*)physics_)
                    ->setProjType(PROJ_FLAK_5);
#ifndef SERVER
                setGraphicsComponent(new FlakTowerL3GraphicsComponent());
#endif
                break;
        }
    }
    connect(getDriver()->getTimer(), SIGNAL(timeout()),
            this, SLOT(update()));
#ifndef SERVER
    connect(CDriver::instance()->getMainWindow(), SIGNAL(signalAltHeld(bool)),
                getGraphicsComponent(), SLOT(setVisibleRange(bool)));
#endif
}

} // end of namespace td

