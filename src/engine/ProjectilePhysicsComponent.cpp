#include "ProjectilePhysicsComponent.h"
#include "Projectile.h"
#include <math.h>
#define PI 3.141592653589793238

ProjectilePhysicsComponent::ProjectilePhysicsComponent() : maxVelocity_(10) {}
ProjectilePhysicsComponent::~ProjectilePhysicsComponent() {}

void ProjectilePhysicsComponent::update(Unit* projectile)
{
    this->makePath((Projectile*)projectile);
    this->setAngle((Projectile*)projectile);
    this->applyVelocity((Projectile*)projectile);
}

void ProjectilePhysicsComponent::applyVelocity(Projectile* projectile) {
    this->path.setLength(this->path.length() - maxVelocity_);
    projectile->setPos(this->path.x2(),this->path.y2());
}

void ProjectilePhysicsComponent::makePath(Projectile* projectile) {
    this->path.setP2(*projectile->getStartPoint());
    this->path.setP1(*projectile->getEndPoint());
}

void ProjectilePhysicsComponent::setAngle(Projectile* projectile) {

    int angle = 0;
    int degree = 0;
    int projX = this->path.x1() - this->path.x2();
    int projY = this->path.y1() - this->path.y2();

    if (projX == 0 && projY == 0) {
        return;
    }

    if (qAbs(projX) >= qAbs(projY)) {
        angle = atan(projX / (float)projY) * (180 / PI);

        if (projX > 0) {
            if (projY == 0) {
                degree = 0;
            } else if (projX == projY) {
                degree = 315;
            } else if (projX == (-projY)) {
                degree = 45;
            } else if (angle < 0) {
                degree =  -angle;
            } else {
                degree = 360 - angle;
            }
        } else if (projX < 0) {
            if (projY == 0) {
                degree = 180;
            } else if (projX == projY) {
                degree = 135;
            } else if (projX == (-projY)) {
                degree = 225;
            } else {
                degree = 180 - angle;
            }
        }
    } else if (qAbs(projY) > qAbs(projX)) {
        angle = atan(projY / (float) projX) * (180 / PI);

        if (projY < 0) {
            if (projX == 0) {
                degree = 90;
            } else {
                degree = 90 + angle;
            }
        } else if (projY > 0) {
            if (projX == 0) {
                degree = 270;
            } else {
                degree = 270 + angle;
            }
        }
    }
    projectile->setOrientation(degree);
}
