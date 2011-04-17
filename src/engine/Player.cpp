#include "Player.h"
#include "Driver.h"
#include "CDriver.h"
#include "BuildingTower.h"
#include "tile.h"
#include "EffectTypes.h"
#include "../graphics/PlayerGraphicsComponent.h"
#include "../audio/SfxManager.h"
#include "../graphics/Console.h"
#include "Resource.h"

namespace td {

Player::Player(QObject* parent)
        : Unit(parent), nickname_(""), harvesting_(RESOURCE_NONE),
          harvestCountdown_(HARVEST_COUNTDOWN), resource_(RESOURCE_NONE) {
    QVector2D force(0, 0);
    this->setForce(force);

    QPointF homeLocation = getDriver()->getGameMap()->getHomeLoc();
    this->setPos(homeLocation.x(), homeLocation.y());
}

Player::~Player()
{
    // Remove the unit from the map before deleting it
    this->getDriver()->getGameMap()->removeUnit(getPos().x(), getPos().y(), this);
}

void Player::networkRead(Stream* s) {
    Unit::networkRead(s);

    if (dirty_ & kNickname) {
        int len = s->readInt();
        nickname_ = QString(s->read(len));
    }
    if (dirty_ & kResource) {
        resource_ = s->readInt();
    }
    if (dirty_ & kMoving) {
        isMoving_ = s->readInt();
    }
}

void Player::networkWrite(Stream* s) {
    Unit::networkWrite(s);

    if (dirty_ & kNickname) {
        s->writeInt(nickname_.length());
        s->write(nickname_.toAscii());
    }
    if (dirty_ & kResource) {
        s->writeInt(resource_);
    }

    if (dirty_ & kMoving) {
        s->writeInt(isMoving_);
    }
}

void Player::initComponents() {
#ifndef SERVER
    /* Client-side has a Graphics Component */
    graphics_ = new PlayerGraphicsComponent(nickname_);
    graphics_->update(this);
#endif
}

void Player::update() {
    if (physics_ != NULL) {
        physics_->update(this);

        bool moving = velocity_.length() != 0;
        if (isMoving_ != moving) {
            isMoving_ = moving;
            setDirty(kMoving);
        }
    }
    if (isDirty()) {
        getDriver()->updateRT(this);
    }
    foreach (Effect* e, effects_) {
        e->update();
    }

    if (graphics_ != NULL) {
        graphics_->update(this);
    }
    if (harvesting_ != RESOURCE_NONE) {
        harvestResource();
    }

    if (physics_ != NULL) {
        tileThatPlayerIsOn_ = getDriver()->getGameMap()->getTile(getPos());
        int tileEffect = getDriver()->getGameMap()->getTile(getPos())->getTileEffect();
        switch(tileEffect) {
            case Tile::NONE:
                break;
            case Tile::SLOW:
                createEffect(EFFECT_SLOW);
                break;
            case Tile::FAST:
                createEffect(EFFECT_FAST);
                break;
            default:
                break;
        }
    }

    emit signalPlayerMovement(getPos());
}

void Player::createEffect(int effectType)
{
    // Check to see if this effect is already applied
    if (!effects_.contains(effectType))
    {
        Effect* effect;

        // Create the effect
        switch (effectType)
        {
        case EFFECT_FAST:
            if(effects_.contains(EFFECT_NPCPLAYER)) {
                return;
            }
            if(effects_.contains(EFFECT_FAST)) {
                return;
            }
            effect = new PlayerTerrainFastEffect(this);
            break;
        case EFFECT_SLOW:
            if(effects_.contains(EFFECT_NPCPLAYER)) {
                return;
            }
            if(effects_.contains(EFFECT_SLOW)) {
                return;
            }
            effect = new PlayerTerrainSlowEffect(this);
            break;
        case EFFECT_NPCPLAYER:
            foreach(Effect* e, effects_) {
                deleteEffect(e);
            }
            effect = new NPCPlayerEffect(this);
            break;
        default:
            return;
        }

        // Dean's sound signal thing
        emit signalEmptyEffectList();

        // Insert the effect into the map
        effects_.insert(effectType, effect);
    }
}

void Player::deleteEffect(Effect* effect)
{
    effects_.remove(effect->getType());
    delete effect;
    effect = NULL;
}

void Player::startHarvesting(int type) {
    if (resource_ != RESOURCE_NONE) {
        return;
    }
    harvesting_ = type;
    emit signalPlayerMovement(false);
    switch (type) {
        case RESOURCE_WOOD:
            PLAY_LOCAL_SFX(SfxManager::resourceWood);
            break;
        case RESOURCE_STONE:
            PLAY_LOCAL_SFX(SfxManager::resourceStone);
            break;
        case RESOURCE_BONE:
            PLAY_LOCAL_SFX(SfxManager::resourceBone);
            break;
        case RESOURCE_TAR:
            PLAY_LOCAL_SFX(SfxManager::resourceTar);
            break;
    }
}

void Player::stopHarvesting() {
    if (harvesting_ == RESOURCE_NONE) {
        return;
    }

    harvesting_ = RESOURCE_NONE;
    harvestCountdown_ = HARVEST_COUNTDOWN;
    emit signalPlayerMovement(true);
}

void Player::dropResource(bool addToTower) {

    if (resource_ == RESOURCE_NONE) {
        return;
    }
    setDirty(kResource);
    if (addToTower) {
#ifndef SERVER
        if (((CDriver*)getDriver())->isSinglePlayer()) {
            Tile* cTile = getDriver()->getGameMap()->getTile(getPos());
            BuildingTower* t = (BuildingTower*)cTile->getExtension();
            if (t->isDone()) {
                getDriver()->createTower(t->getType(), t->getPos());
                getDriver()->destroyObject(t);
            }
        }
        Console::instance()->addText("Added Resource");
#endif
    } else {
        emit signalDropResource(resource_, pos_, getRandomVector());
#ifndef SERVER
        Console::instance()->addText("Dropped Resource");
#endif
    }
    resource_ = RESOURCE_NONE;
}

void Player::harvestResource() {
    if (--harvestCountdown_ <= 0) {
        resource_ = harvesting_;
        harvestCountdown_ = HARVEST_COUNTDOWN;
        setDirty(kResource);
        stopHarvesting();

#ifndef SERVER
    Console::instance()->addText("Picked up a Resource");
#endif

    return;
    }
}
void Player::pickupCollectable(double x, double y, Unit* u) {

    // First check to see if the collectable is a gem
    if(((Collectable*)u)->getType() == RESOURCE_GEM) {
        // Remove the gem from the tile and increment the global counter
        Tile* t = getDriver()->getGameMap()->getTile(x, y);
        t->removeUnit(u);
        // Disconnect from the timer
        disconnect(getDriver()->getTimer(),  SIGNAL(timeout()), u, SLOT(update()));
        //increment global gem count here.
        getDriver()->destroyObject(u);
        return;
    }

    // Check to see if we are already carrying a resource
    if (resource_ != RESOURCE_NONE)
    {
        return;
    }

    Tile* t = getDriver()->getGameMap()->getTile(x, y);
    t->removeUnit(u);
    disconnect(getDriver()->getTimer(),  SIGNAL(timeout()), u, SLOT(update()));
    resource_ = ((Collectable*)u)->getType();
    setDirty(kResource);
    getDriver()->destroyObject(u);
}
} /* end namespace td */
