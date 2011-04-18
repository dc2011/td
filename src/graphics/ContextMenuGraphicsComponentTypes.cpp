#include "ContextMenuGraphicsComponentTypes.h"
#include "../engine/CDriver.h"
#include "../engine/ContextMenu.h"
#include "../engine/Map.h"
#include "../engine/Tower.h"
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
    initTowerRanges();
}

void BuildContextMenuGraphicsComponent::initTowerRanges() {
    int i;
    QPen pen;
    pen.setWidth(3);
    for (i = 0; i != TOWER_TYPE_MAX;++i) {
        circleRanges_[i] = new QGraphicsEllipseItem();
    }
    pen.setColor(ARROW_COLOR);
    circleRanges_[0]->setPen(pen);
    pen.setColor(CANNON_COLOR);
    circleRanges_[1]->setPen(pen);
    pen.setColor(TAR_COLOR);
    circleRanges_[2]->setPen(pen);
    pen.setColor(FLAME_COLOR);
    circleRanges_[3]->setPen(pen);
    pen.setColor(FLAK_COLOR);
    circleRanges_[4]->setPen(pen);

    for (i = 0; i != TOWER_TYPE_MAX; ++i) {
        circleRanges_[i]->setBrush(QBrush(Qt::transparent));
        CDriver::instance()->getMainWindow()->getScene()->
                addItem(circleRanges_[i]);
    }
}

void BuildContextMenuGraphicsComponent::draw(void* dp, int layer) {
    QPointF point = ((DrawParamsMenuGraphics*) dp)->pos;
    
    // move the radii off screen if alt is not held down 
    if (((DrawParamsMenuGraphics*) dp)->pixmapIdx != 1) {
        point.setX(OFFSCREEN);
        point.setY(OFFSCREEN);
    }
        
    int radius = RADIUS_ARROW;
    circleRanges_[0]->setRect(point.x()-radius, point.y()-radius, 
                              radius * 2, radius * 2);
    radius = RADIUS_CANNON;
    circleRanges_[1]->setRect(point.x()-radius, point.y()-radius,
                              radius * 2, radius * 2);
    radius = RADIUS_TAR;
    circleRanges_[2]->setRect(point.x()-radius, point.y()-radius,
                              radius * 2, radius * 2);
    radius = RADIUS_FLAME;
    circleRanges_[3]->setRect(point.x()-radius, point.y()-radius,
                              radius * 2, radius * 2);
    radius = RADIUS_FLAK;
    circleRanges_[4]->setRect(point.x()-radius, point.y()-radius,
                              radius * 2, radius * 2);

    ContextMenuGraphicsComponent::draw(dp,layer);
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
    Map* map = CDriver::instance()->getGameMap();
    QPointF pos = menu_->getPos();
    Tile* tile = map->getTile(pos.x(), pos.y());
    int towerLevel = 0;
   
    if (tile->getExtension() != NULL) {
        towerLevel = ((Tower*) tile->getExtension())->getLevel();
    }
    
    if (nextImage_ == MENU_BASE) {
        if (towerLevel < MAX_TOWER_LEVEL) { 
            return MENU_BASE;
        }
        return MENU_TOWER_UPGRADE_ALL;
    }
    if (nextImage_ == MENU_RESOURCES) {
        return towerLevel + 1;
    }
    return ContextMenuGraphicsComponent::getCurrentImage();
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
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_MAIN_2;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_MAIN_3;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_MAIN_4;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_MAIN_5;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_MAIN_6;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_MAIN_7;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_MAIN_8;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES_2;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES_3;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES_4;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES_5;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES_6;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES_7;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES_8;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_SPD;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_HAR;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_REC;
    pixmapIndex_ = 0;
}

void PlayerContextMenuGraphicsComponent::showSelectMenu(int type,
                                                        QPointF playerPos) {
    switch(type) {
        case UPGRADE_SPEED:
            nextImage_ = 16;
            break;
        case UPGRADE_HARVEST:
            nextImage_ = 17;
            break;
        case UPGRADE_RECOVERY:
            nextImage_ = 18;
            break;
    }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* PlayerContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

int PlayerContextMenuGraphicsComponent::getCurrentImage() {
    
    if (nextImage_ == MENU_BASE) {
        return menu_->getPlayer()->getUpgrades(); 
    }
    if (nextImage_ == MENU_RESOURCES) {
        return menu_->getPlayer()->getUpgrades() + 8; 
    }
    return ContextMenuGraphicsComponent::getCurrentImage();
}

} // end namespace td

