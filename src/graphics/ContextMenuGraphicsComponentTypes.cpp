#include "ContextMenuGraphicsComponentTypes.h"
#include "../engine/ContextMenu.h"
#include "../util/defines.h"

namespace td {

QPixmap* BuildContextMenuGraphicsComponent::pixmapImgs_ = 0;

BuildContextMenuGraphicsComponent::BuildContextMenuGraphicsComponent(
        ContextMenu* menu)
        : ContextMenuGraphicsComponent(menu) {
    emit created(this);
}

void BuildContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_BUILD_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T1;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T2;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T3;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T4;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T5;
    pixmapIndex_ = 0;
}

void BuildContextMenuGraphicsComponent::showSelectMenu(int type,
                                                       QPointF playerPos) {
    switch(type) {
        case TOWER_ARROW:
            nextImage_ = 2;
            break;
        case TOWER_CANNON:
            nextImage_ = 3;
            break;
        case TOWER_FLAME:
            nextImage_ = 4;
            break;
        case TOWER_TAR:
            nextImage_ = 5;
            break;
        case TOWER_FLAK:
            nextImage_ = 6;
            break;
        }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* BuildContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

int BuildContextMenuGraphicsComponent::getCurrentImage() {
    if (nextImage_ == MENU_BASE) {
        if (menu_->getUpgradeLevels() < MAX_TOWER_LEVEL) {
            return MENU_BASE;
        }
        return MENU_UPGRADE_ALL;
    }
    if (nextImage_ == MENU_TOWER_RESOURCES) {
        return menu_->getUpgradeLevels() + MENU_TOWER_RESOURCES;
    }
    ContextMenuGraphicsComponent::getCurrentImage();
}


QPixmap* TowerContextMenuGraphicsComponent::pixmapImgs_ = 0;

TowerContextMenuGraphicsComponent::TowerContextMenuGraphicsComponent(
        ContextMenu* menu)
        : ContextMenuGraphicsComponent(menu) {
    emit created(this);
}

void TowerContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_TOWER_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_MAIN_2;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_RES_L1;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_RES_L2;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_RES_L3;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_RES_L4;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_RES_L5;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_UPGR;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_SELL;
    pixmapIndex_ = 0;
}

void TowerContextMenuGraphicsComponent::showSelectMenu(int type,
                                                       QPointF playerPos) {
    switch(type) {
        case UPGRADE_TOWER:
            nextImage_ = MENU_TOWER_UPGRADE;
            break;
        case SELL_TOWER:
            nextImage_ = MENU_TOWER_SELL;
            break;
        }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* TowerContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

int TowerContextMenuGraphicsComponent::getCurrentImage() {
    if (nextImage_ == MENU_BASE) {
        if (menu_->getUpgradeLevels() < MAX_TOWER_LEVEL) {
            return MENU_BASE;
        }
        return MENU_UPGRADE_ALL;
    }
    if (nextImage_ == MENU_TOWER_RESOURCES) {
        return menu_->getUpgradeLevels() + MENU_TOWER_RESOURCES;
    }
    ContextMenuGraphicsComponent::getCurrentImage();
}

QPixmap* PlayerContextMenuGraphicsComponent::pixmapImgs_ = 0;

PlayerContextMenuGraphicsComponent::PlayerContextMenuGraphicsComponent(
        ContextMenu* menu)
        : ContextMenuGraphicsComponent(menu) {
    emit created(this);
}

void PlayerContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PLAYER_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_SPD;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_HAR;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_REC;
    pixmapIndex_ = 0;
}

void PlayerContextMenuGraphicsComponent::showSelectMenu(int type,
                                                        QPointF playerPos) {
    switch(type) {
        case UPGRADE_SPEED:
            nextImage_ = 2;
            break;
        case UPGRADE_HARVEST:
            nextImage_ = 3;
            break;
        case UPGRADE_RECOVERY:
            nextImage_ = 4;
            break;
        }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* PlayerContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

int PlayerContextMenuGraphicsComponent::getCurrentImage() {
    if (nextImage_ == MENU_BASE) {
        if (menu_->getUpgradeLevels() < MAX_TOWER_LEVEL) {
            return MENU_BASE;
        }
        return MENU_UPGRADE_ALL;
    }
    if (nextImage_ == MENU_TOWER_RESOURCES) {
        return menu_->getUpgradeLevels() + MENU_TOWER_RESOURCES;
    }
    ContextMenuGraphicsComponent::getCurrentImage();
}

} // end namespace td

