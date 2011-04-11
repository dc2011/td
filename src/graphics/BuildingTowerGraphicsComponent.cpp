#include "BuildingTowerGraphicsComponent.h"
#include "../engine/BuildingTower.h"
#include "../engine/CDriver.h"
#include <QRectF>

namespace td {

    bool BuildingTowerGraphicsComponent::keyHeld_ = false;

QPixmap* BuildingTowerGraphicsComponent::pixmapImgs_ = NULL;

BuildingTowerGraphicsComponent::BuildingTowerGraphicsComponent()
        : GraphicsComponent() {
    animate_ = 0;
    emit created(this);
}

BuildingTowerGraphicsComponent::~BuildingTowerGraphicsComponent() {
    int i;
    for (i = 0; i != RESOURCE_TYPE_MAX; i++) {
        delete[] resourcePixmapItemArray_[i];
    }
}

void BuildingTowerGraphicsComponent::draw(DrawParams* dp, int layer)  {
    int i;
    int quarter;
    int half;
    int threequarters;
    QRectF rect = getPixmapItem()->boundingRect();
    quarter = rect.width() * .25;
    half = rect.width() * .5;
    threequarters = rect.width() * .75;

    for (i = 0; i != ICON_MAX; i++) {
        iconDrawingHelper(resourcePixmapItemArray_[RESOURCE_WOOD-1][i], dp->pos.x(), dp->pos.y(),layer,i,woodReq_);
        resourcePixmapItemArray_[RESOURCE_WOOD-1][i]->setPixmap(pixmapImgs_[PIX_BUILDING_TOWER_MAX]);
        iconDrawingHelper(resourcePixmapItemArray_[RESOURCE_STONE-1][i], dp->pos.x() + quarter, dp->pos.y(),layer,i,stoneReq_);
        resourcePixmapItemArray_[RESOURCE_STONE-1][i]->setPixmap(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 1]);
        iconDrawingHelper(resourcePixmapItemArray_[RESOURCE_BONE-1][i], dp->pos.x() + half, dp->pos.y(),layer,i,boneReq_);
        resourcePixmapItemArray_[RESOURCE_BONE-1][i]->setPixmap(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 2]);
        iconDrawingHelper(resourcePixmapItemArray_[RESOURCE_TAR-1][i], dp->pos.x() + threequarters, dp->pos.y(),layer,i,tarReq_);
        resourcePixmapItemArray_[RESOURCE_TAR-1][i]->setPixmap(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 3]);
    }
    GraphicsComponent::draw(dp, layer - 1);
}

void BuildingTowerGraphicsComponent::iconDrawingHelper(QGraphicsPixmapItem *icon, int x, int y, int layer, int i, int resourceReq) {
    int yoffset = getPixmapItem()->boundingRect().width() / 5;
    int center = getPixmapItem()->boundingRect().center().x();
    icon->setPos(x - center, y + i * yoffset - center);
    icon->setZValue(layer);
    icon->setScale(.5);
    //setIconVisibility(icon, i, resourceReq);
}

void BuildingTowerGraphicsComponent::initPixmaps() {
    //resourcePixmapItemArray_ = new QGraphicsPixmapItem[RESOURCE_TYPE_MAX][ICON_MAX];

    if (pixmapImgs_ != NULL) {
        setIconImages();
    }

    pixmapImgs_ = new QPixmap[PIX_BUILDING_TOWER_MAX + RESOURCE_TYPE_MAX];
    pixmapImgs_[pixmapIndex_++] = PIX_BUILDING_TOWER_25;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILDING_TOWER_50;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILDING_TOWER_75;
    pixmapImgs_[pixmapIndex_++] = PIX_ICON_WOOD;
    pixmapImgs_[pixmapIndex_++] = PIX_ICON_STONE;
    pixmapImgs_[pixmapIndex_++] = PIX_ICON_BONE;
    pixmapImgs_[pixmapIndex_++] = PIX_ICON_TAR;
    pixmapIndex_ = 0;
    setIconImages();
}

void BuildingTowerGraphicsComponent::update(GameObject* obj) {
    BuildingTower* tower = (BuildingTower*)obj;
    if (!tower->isDirty()) {
        //checks if object is dirty or in mid-animation, or if the resource progress
        //bar is being updated
        return;
    }
    tower->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = tower->getPos();
    dp->moving  = 1;
    dp->scale   = 1;
    dp->degrees = 0;
    emit signalDraw(dp, this, LAYER_TOWER);
}

void BuildingTowerGraphicsComponent::setBuildingResources(int resourceType, int num) {
    switch (resourceType) {
    case RESOURCE_WOOD:
        woodReq_ = num;
        break;
    case RESOURCE_STONE:
        stoneReq_ = num;
        break;
    case RESOURCE_BONE:
        boneReq_ = num;
        break;
    case RESOURCE_TAR:
        tarReq_ = num;
        break;
    }
}

void BuildingTowerGraphicsComponent::setIconImages() {
    int i, j;
    for (i = 0; i != ICON_MAX; i++) {
        resourcePixmapItemArray_[RESOURCE_WOOD-1][i] = new QGraphicsPixmapItem(pixmapImgs_[PIX_BUILDING_TOWER_MAX]);
        resourcePixmapItemArray_[RESOURCE_WOOD-1][i]->setVisible(false);
        resourcePixmapItemArray_[RESOURCE_STONE-1][i] = new QGraphicsPixmapItem(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 1]);
        resourcePixmapItemArray_[RESOURCE_STONE-1][i]->setVisible(false);
        resourcePixmapItemArray_[RESOURCE_BONE-1][i] = new QGraphicsPixmapItem(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 2]);
        resourcePixmapItemArray_[RESOURCE_BONE-1][i]->setVisible(false);
        resourcePixmapItemArray_[RESOURCE_TAR-1][i] = new QGraphicsPixmapItem(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 3]);
        resourcePixmapItemArray_[RESOURCE_TAR-1][i]->setVisible(false);
    }
    for (i = 0; i != ICON_MAX; i++) {
        for (j = 0; j != RESOURCE_TYPE_MAX; j++) {
            CDriver::instance()->getMainWindow()->getScene()->addItem(resourcePixmapItemArray_[j][i]);
        }
    }
}

void BuildingTowerGraphicsComponent::setIconVisibility(QGraphicsPixmapItem *iconGraphic, int index, int resourceReq) {
    if (index < resourceReq) {
        iconGraphic->setVisible(true);
    } else {
        iconGraphic->setVisible(false);
    }
}

void BuildingTowerGraphicsComponent::showIcons(bool keyHeld) {
    static bool held = false;
    int i, j;
    if (keyHeld) {
        for (i = 0; i != ICON_MAX; i++) {
            setIconVisibility(resourcePixmapItemArray_[RESOURCE_WOOD-1][i], i, woodReq_);
            setIconVisibility(resourcePixmapItemArray_[RESOURCE_STONE-1][i], i, stoneReq_);
            setIconVisibility(resourcePixmapItemArray_[RESOURCE_TAR-1][i], i, tarReq_);
            setIconVisibility(resourcePixmapItemArray_[RESOURCE_BONE-1][i], i, boneReq_);
        }
    } else {
        for (i = 0; i != ICON_MAX; i++) {
            for (j = 0; j != RESOURCE_TYPE_MAX; j++) {
                resourcePixmapItemArray_[j][i]->setVisible(keyHeld);
            }
        }
    }
}


} /* end namespace td */

