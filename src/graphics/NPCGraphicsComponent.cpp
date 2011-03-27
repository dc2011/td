#include "NPCGraphicsComponent.h"
#include "../engine/NPC.h"

namespace td {

QPixmap * NPCGraphicsComponent::pixmapImgs_ = 0;

NPCGraphicsComponent::NPCGraphicsComponent()
        : GraphicsComponent() {
    emit created(this);
}

/*
NPCGraphicsComponent::NPCGraphicsComponent(int npcType)
    : GraphicsComponent(), npcType_(npcType) {
    emit created(this);
}
*/

NPCGraphicsComponent::~NPCGraphicsComponent() {}

void NPCGraphicsComponent::showHealth(bool keyHeld) {
    showHealth_ = keyHeld;
}

QPixmap * NPCGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

void NPCGraphicsComponent::animate() {
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ > arrayIndexMax_ ? pixmapIndex_ = arrayIndexMin_
            : pixmapIndex_;
        setImgIndex(pixmapIndex_);

    }
}

} /* end namespace td */
