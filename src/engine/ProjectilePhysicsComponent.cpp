#include "ProjectilePhysicsComponent.h"
#include "Projectile.h"
#include <math.h>
#define PI 3.141592653589793238

ProjectilePhysicsComponent::ProjectilePhysicsComponent()
    : maxVelocity_(10), duration_(-1), increment_(0) {}
ProjectilePhysicsComponent::~ProjectilePhysicsComponent() {}

void ProjectilePhysicsComponent::update(Unit* projectile)
{
    if (((Projectile*)projectile)->getPath().length() >= maxVelocity_) {
        this->applyDirection((Projectile*)projectile);
        this->applyVelocity((Projectile*)projectile);
        this->setScale((Projectile*)projectile);
    }
}

void ProjectilePhysicsComponent::applyVelocity(Projectile* projectile) {
    projectile->getPath().setLength(projectile->getPath().length() - maxVelocity_);
    projectile->setPos(projectile->getPath().x2(), projectile->getPath().y2());
}

void ProjectilePhysicsComponent::applyDirection(Projectile* projectile) {

    int angle = 0;
    int degree = 0;
    int projX = projectile->getPath().x1() - projectile->getPath().x2();
    int projY = projectile->getPath().y1() - projectile->getPath().y2();

    if (projX == 0 && projY == 0) {
        return;
    }

    if (qAbs(projX) >= qAbs(projY)) {
        angle = atan(projY / (float)projX) * (180 / PI);

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
        angle = atan(projX / (float) projY) * (180 / PI);

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

void ProjectilePhysicsComponent::setScale(Projectile *projectile) {

    if (duration_ < 0) {
        duration_ = projectile->getPath().length() / maxVelocity_;
        increment_ = 0;
    }

    if (increment_++ < (duration_ / 2)) {
        projectile->setScale(projectile->getScale() + 0.05);
    } else if (increment_ < duration_) {
        projectile->setScale(projectile->getScale() - 0.05);
    }

}
