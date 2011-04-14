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

    this->setPos(100, 100);
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
    }
    if (isDirty()) {
        getDriver()->updateRT(this);
    }

    for(QMap<int, Effect*>::iterator it = effects_.begin();
        it != effects_.end(); ++it) {
        it.value()->update();
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
            effect = new PlayerTerrainFastEffect(this);
            break;
        case EFFECT_SLOW:
            effect = new PlayerTerrainSlowEffect(this);
            break;
        case EFFECT_NPCPLAYER:
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
    if (getGraphicsComponent()) {
        getGraphicsComponent()->setCurrentResource(RESOURCE_NONE);
    }
}

void Player::harvestResource() {
    if (--harvestCountdown_ <= 0) {
        resource_ = harvesting_;
        harvestCountdown_ = HARVEST_COUNTDOWN;
        if (getGraphicsComponent()) {
            getGraphicsComponent()->setCurrentResource(resource_);
            getGraphicsComponent()->update(this);

        }
        setDirty(kResource);
        stopHarvesting();

#ifndef SERVER
	Console::instance()->addText("Picked up a Resource");
#endif

	return;
    }
}
void Player::pickupCollectable(double x, double y, Unit* u) {
    Tile* t = getDriver()->getGameMap()->getTile(x, y);
    t->removeUnit(u);
    if(((Collectable*)u)->getType() == RESOURCE_GEM) {
        //increment global gem count here.
        getDriver()->destroyObject(u);
        return;
    }

    resource_ = ((Collectable*)u)->getType();
    if (getGraphicsComponent()) {
        getGraphicsComponent()->setCurrentResource(resource_);
        getGraphicsComponent()->update(this);

    }
    setDirty(kResource);
    getDriver()->destroyObject(u);
}
} /* end namespace td */
