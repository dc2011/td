
#include "EndingGraphicsComponent.h"

namespace td {

EndingGraphicsComponent::EndingGraphicsComponent() : GraphicsComponent() {

}

EndingGraphicsComponent::~EndingGraphicsComponent() {
    disconnect(this);
}

void EndingGraphicsComponent::update(GameObject* obj) {

}

void EndingGraphicsComponent::draw(DrawParams *dp, int layer) {

}

void EndingGraphicsComponent::animate() {

}

// cannon ending animation

QPixmap* CannonEndingGraphicsComponent::pixmapImgs_ = NULL;

CannonEndingGraphicsComponent::CannonEndingGraphicsComponent() {

}

CannonEndingGraphicsComponent::~CannonEndingGraphicsComponent() {

}

}
