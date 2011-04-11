#include "ProjectileInputComponentTypes.h"
#include "../engine/Projectile.h"
#include "../engine/NPC.h"
#include "../engine/EffectTypes.h"
#include <QPointF>

namespace td {
    
void ArrowProjectileInputComponent::update() {
    if (parent_->getEnemy() != NULL) {
        QPointF* start = new QPointF(parent_->getPos().x(),
                                     parent_->getPos().y());
        QPointF* end = new QPointF(parent_->getEnemy()->getPos().x(),
                                   parent_->getEnemy()->getPos().y());
        setPath(start, end);
    }
    makeForce();
}

void TarProjectileInputComponent::update() {
    if (parent_->getEnemy() != NULL) {
        QPointF* start = new QPointF(parent_->getPos().x(),
                                     parent_->getPos().y());
        QPointF* end = new QPointF(parent_->getEnemy()->getPos().x(),
                                   parent_->getEnemy()->getPos().y());
        setPath(start, end);
    }
    makeForce();
}

void ArrowProjectileInputComponent::checkNPCCollision(QSet<Unit*> npcs){
    QSet<Unit*>::iterator it;
    QPolygonF projBounds;
    QPolygonF npcBounds;

//Note: for arrow/flak/other autohit projectiles
// Just need to add effect to this->getEnemy()

    for (it = npcs.begin(); it != npcs.end(); ++it) {
        if ((((*it)->getID() & 0xFF000000)>>24) == NPC::clsIdx()) {
            // Check to see if this projectile can damage this unit
            if ((parent_->getType() == PROJ_FLAK) && (((NPC*)*it)->getType() != NPC_FLY))
            {
                continue;
            }
            if ((((NPC*)*it)->getType() == NPC_FLY)
                && ((parent_->getType() == PROJ_CANNON) || (parent_->getType() == PROJ_FIRE)
                    || (parent_->getType() == PROJ_TAR)))
            {
                continue;
            }

            projBounds = parent_->getBounds();
            npcBounds = (*it)->getBounds();
            if(parent_->getBounds().intersected((*it)->getBounds()).count() != 0){
                //create projectile effect
                //add effect to npc
                //qDebug("Enemy hit");
                ((NPC*)(*it))->createEffect(new ArrowEffect(*it));
                break;
            }else{
                //qDebug("No hit");
            }

        }
    }

}

void TarProjectileInputComponent::checkNPCCollision(QSet<Unit*> npcs){
    QSet<Unit*>::iterator it;
    QPolygonF projBounds;
    QPolygonF npcBounds;

//Note: for arrow/flak/other autohit projectiles
// Just need to add effect to this->getEnemy()

    for (it = npcs.begin(); it != npcs.end(); ++it) {
        if ((((*it)->getID() & 0xFF000000)>>24) == NPC::clsIdx()) {
            // Check to see if this projectile can damage this unit
            if ((parent_->getType() == PROJ_FLAK) && (((NPC*)*it)->getType() != NPC_FLY))
            {
                continue;
            }
            if ((((NPC*)*it)->getType() == NPC_FLY)
                && ((parent_->getType() == PROJ_CANNON) || (parent_->getType() == PROJ_FIRE)
                    || (parent_->getType() == PROJ_TAR)))
            {
                continue;
            }

            projBounds = parent_->getBounds();
            npcBounds = (*it)->getBounds();
            if(parent_->getBounds().intersected((*it)->getBounds()).count() != 0){
                //create projectile effect
                //add effect to npc
                //qDebug("Enemy hit");
                ((NPC*)(*it))->createEffect(new NPCTarEffect(*it));
                break;
            }else{
                //qDebug("No hit");
            }

        }
    }

}

void FlakProjectileInputComponent::checkNPCCollision(QSet<Unit*> npcs){
    QSet<Unit*>::iterator it;
    QPolygonF projBounds;
    QPolygonF npcBounds;

//Note: for arrow/flak/other autohit projectiles
// Just need to add effect to this->getEnemy()

    for (it = npcs.begin(); it != npcs.end(); ++it) {
        if ((((*it)->getID() & 0xFF000000)>>24) == NPC::clsIdx()) {
            // Check to see if this projectile can damage this unit
            if ((parent_->getType() == PROJ_FLAK) && (((NPC*)*it)->getType() != NPC_FLY))
            {
                continue;
            }
            if ((((NPC*)*it)->getType() == NPC_FLY)
                && ((parent_->getType() == PROJ_CANNON) || (parent_->getType() == PROJ_FIRE)
                    || (parent_->getType() == PROJ_TAR)))
            {
                continue;
            }

            projBounds = parent_->getBounds();
            npcBounds = (*it)->getBounds();
            if(parent_->getBounds().intersected((*it)->getBounds()).count() != 0){
                //create projectile effect
                //add effect to npc
                //qDebug("Enemy hit");
                ((NPC*)(*it))->createEffect(new NPCTarEffect(*it));
                break;
            }else{
                //qDebug("No hit");
            }

        }
    }

}

void FireProjectileInputComponent::checkNPCCollision(QSet<Unit*> npcs){
    QSet<Unit*>::iterator it;
    QPolygonF projBounds;
    QPolygonF npcBounds;

//Note: for arrow/flak/other autohit projectiles
// Just need to add effect to this->getEnemy()

    for (it = npcs.begin(); it != npcs.end(); ++it) {
        if ((((*it)->getID() & 0xFF000000)>>24) == NPC::clsIdx()) {
            // Check to see if this projectile can damage this unit
            if ((parent_->getType() == PROJ_FLAK) && (((NPC*)*it)->getType() != NPC_FLY))
            {
                continue;
            }
            if ((((NPC*)*it)->getType() == NPC_FLY)
                && ((parent_->getType() == PROJ_CANNON) || (parent_->getType() == PROJ_FIRE)
                    || (parent_->getType() == PROJ_TAR)))
            {
                continue;
            }

            projBounds = parent_->getBounds();
            npcBounds = (*it)->getBounds();
            if(parent_->getBounds().intersected((*it)->getBounds()).count() != 0){
                //create projectile effect
                //add effect to npc
                //qDebug("Enemy hit");
                ((NPC*)(*it))->createEffect(new NPCTarEffect(*it));
                break;
            }else{
                //qDebug("No hit");
            }

        }
    }

}

void CannonProjectileInputComponent::checkNPCCollision(QSet<Unit*> npcs){
    QSet<Unit*>::iterator it;
    QPolygonF projBounds;
    QPolygonF npcBounds;

//Note: for arrow/flak/other autohit projectiles
// Just need to add effect to this->getEnemy()

    for (it = npcs.begin(); it != npcs.end(); ++it) {
        if ((((*it)->getID() & 0xFF000000)>>24) == NPC::clsIdx()) {
            // Check to see if this projectile can damage this unit
            if ((parent_->getType() == PROJ_FLAK) && (((NPC*)*it)->getType() != NPC_FLY))
            {
                continue;
            }
            if ((((NPC*)*it)->getType() == NPC_FLY)
                && ((parent_->getType() == PROJ_CANNON) || (parent_->getType() == PROJ_FIRE)
                    || (parent_->getType() == PROJ_TAR)))
            {
                continue;
            }

            projBounds = parent_->getBounds();
            npcBounds = (*it)->getBounds();
            if(parent_->getBounds().intersected((*it)->getBounds()).count() != 0){
                //create projectile effect
                //add effect to npc
                //qDebug("Enemy hit");
                ((NPC*)(*it))->createEffect(new NPCTarEffect(*it));
                break;
            }else{
                //qDebug("No hit");
            }

        }
    }

}

} /* end namespace td */
