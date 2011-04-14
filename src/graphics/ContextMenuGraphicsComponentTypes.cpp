#include "ContextMenuGraphicsComponentTypes.h";

#define ARROW_TOWER_SELECTED    49
#define CANNON_TOWER_SELECTED   50
#define FLAME_TOWER_SELECTED    51
#define TAR_TOWER_SELECTED      52
#define FLAK_TOWER_SELECTED     53

namespace td {

QPixmap* BuildContextMenuGraphicsComponent::pixmapImgs_ = 0;

BuildContextMenuGraphicsComponent::BuildContextMenuGraphicsComponent()
        : ContextMenuGraphicsComponent() {
    emit created(this);
}

void BuildContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_CONTEXT_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T1;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T2;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T3;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T4;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T5;
    pixmapIndex_ = 0;
}

void BuildContextMenuGraphicsComponent::showSelectMenu(int type,
                                                       QPointF playerPos) {
    switch(type) {
        case ARROW_TOWER_SELECTED:
            nextImage_ = 2;
            break;
        case CANNON_TOWER_SELECTED:
            nextImage_ = 3;
            break;
        case FLAME_TOWER_SELECTED:
            nextImage_ = 4;
            break;
        case TAR_TOWER_SELECTED:
            nextImage_ = 5;
            break;
        case FLAK_TOWER_SELECTED:
            nextImage_ = 6;
            break;
        }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* BuildContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

QPixmap* TowerContextMenuGraphicsComponent::pixmapImgs_ = 0;

TowerContextMenuGraphicsComponent::TowerContextMenuGraphicsComponent()
        : ContextMenuGraphicsComponent() {
    emit created(this);
}

void TowerContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_CONTEXT_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T1;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T2;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T3;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T4;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T5;
    pixmapIndex_ = 0;
}

void TowerContextMenuGraphicsComponent::showSelectMenu(int type,
                                                       QPointF playerPos) {
    switch(type) {
        case ARROW_TOWER_SELECTED:
            nextImage_ = 2;
            break;
        case CANNON_TOWER_SELECTED:
            nextImage_ = 3;
            break;
        case FLAME_TOWER_SELECTED:
            nextImage_ = 4;
            break;
        case TAR_TOWER_SELECTED:
            nextImage_ = 5;
            break;
        case FLAK_TOWER_SELECTED:
            nextImage_ = 6;
            break;
        }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* TowerContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

QPixmap* PlayerContextMenuGraphicsComponent::pixmapImgs_ = 0;

PlayerContextMenuGraphicsComponent::PlayerContextMenuGraphicsComponent()
        : ContextMenuGraphicsComponent() {
    emit created(this);
}

void PlayerContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_CONTEXT_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T1;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T2;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T3;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T4;
    pixmapImgs_[pixmapIndex_++] = PIX_CONTEXT_MENU_T5;
    pixmapIndex_ = 0;
}

void PlayerContextMenuGraphicsComponent::showSelectMenu(int type,
                                                        QPointF playerPos) {
    switch(type) {
        case ARROW_TOWER_SELECTED:
            nextImage_ = 2;
            break;
        case CANNON_TOWER_SELECTED:
            nextImage_ = 3;
            break;
        case FLAME_TOWER_SELECTED:
            nextImage_ = 4;
            break;
        case TAR_TOWER_SELECTED:
            nextImage_ = 5;
            break;
        case FLAK_TOWER_SELECTED:
            nextImage_ = 6;
            break;
        }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* PlayerContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

} // end namespace td

