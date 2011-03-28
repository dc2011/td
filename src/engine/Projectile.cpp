#include "Projectile.h"
#include "NPC.h"
#ifndef SERVER
#include "CDriver.h"
#endif
namespace td {

Projectile::Projectile() : Unit() {
    start_ = new QPointF(0,0);
    end_ = new QPointF(0,0);
    scale_ = 0.25;
    path_ = QLineF(end_->x(), end_->y(), start_->x(), start_->y());
    this->pos_ = QPointF(0,0);
    this->setHeight(10);
    this->setWidth(48);
}

void Projectile::networkRead(td::Stream* s) {
    Unit::networkRead(s);

    if (dirty_ & kDamage) {
        damage_ = s->readInt();
    }

    if (dirty_ & kStartPos) {
        start_->setX(s->readFloat());
        start_->setY(s->readFloat());
    }

    if (dirty_ & kEndPos) {
        end_->setX(s->readFloat());
        end_->setY(s->readFloat());
    }
}

void Projectile::networkWrite(td::Stream* s) {
    Unit::networkWrite(s);

    if (dirty_ & kDamage) {
        s->writeInt(damage_);
    }

    if (dirty_ & kStartPos) {
        s->writeFloat(start_->x());
        s->writeFloat(start_->y());
    }

    if (dirty_ & kEndPos) {
        s->writeFloat(end_->x());
        s->writeFloat(end_->y());
    }
}

void Projectile::update() {
#ifndef SERVER
    CDriver::updateServer(this);
#endif
    input_->update();
    physics_->update(this);
    graphics_->update(this);
}

void Projectile::checkNPCCollision(QSet<Unit*> npcs){
    QSet<Unit*>::iterator it;
    QPolygonF projBounds;
    QPolygonF npcBounds;

//Note: for arrow/flak/other autohit projectiles
// Just need to add effect to this->getEnemy()

    for (it = npcs.begin(); it != npcs.end(); ++it) {
        if ((((*it)->getID() & 0xFF000000)>>24) == NPC::clsIdx()){
            projBounds = this->getBounds();
            npcBounds = (*it)->getBounds();
            if(this->getBounds().intersected((*it)->getBounds()).count() != 0){
                //create projectile effect
                //add effect to npc
                //qDebug("Enemy hit");
                break;
            }else{
                //qDebug("No hit");
            }

        }
    }

}

void Projectile::createBounds(){
    QVector<QPointF> points = QVector<QPointF>();
    QPointF *newPos = this->getEndPoint();
    QPointF point;
    QMatrix matrix = QMatrix();
    matrix.rotate(-this->getOrientation());

    point = QPointF(-((this->getWidth()/2) * this->getScale() ),
                        -((this->getHeight( )/2) * this->getScale())) * matrix;
    point += *newPos;
    points.append(point);
    point = QPointF((this->getWidth()/2) * this->getScale(),
                        -((this->getHeight()/2) * this->getScale())) * matrix;
    point += *newPos;
    points.append(point);
    point = QPointF((this->getWidth()/2) * this->getScale(),
                        (this->getHeight()/2) * this->getScale()) * matrix;
    point += *newPos;
    points.append(point);
    point = QPointF(-((this->getWidth()/2) * this->getScale()),
                        (this->getHeight()/2) * this->getScale()) * matrix;
    point += *newPos;
    points.append(point);
    point = QPointF(-((this->getWidth()/2) * this->getScale() ),
                        -((this->getHeight( )/2) * this->getScale())) * matrix;
    point += *newPos;
    points.append(point);

    this->setBounds(QPolygonF(points));
}

} /* end namespace td */
