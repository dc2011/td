#include "BuildingTowerGraphicsComponent.h"
#include "../engine/BuildingTower.h"
#include "../engine/CDriver.h"
#include <QRectF>

namespace td {

QPixmap* BuildingTowerGraphicsComponent::pixmapImgs_ = NULL;

BuildingTowerGraphicsComponent::BuildingTowerGraphicsComponent()
        : GraphicsComponent() {
    animate_ = 0;
    buildingStage_ = 0;
    emit created(this);
}

BuildingTowerGraphicsComponent::~BuildingTowerGraphicsComponent() {
    int i, j;
    this->disconnect();
    for (i = 0; i != RESOURCE_TYPE_MAX; i++) {
        for (j = 0; j != ICON_MAX; j++) {
            CDriver::instance()->getMainWindow()->getScene()->removeItem(resourcePixmapItemArray_[i][j]);
            delete resourcePixmapItemArray_[i][j];
        }
    }
}

void BuildingTowerGraphicsComponent::draw(void* dp, int layer)  {
    int i;
    int quarter;
    int half;
    int threequarters;
    QRectF rect = getPixmapItem()->boundingRect();
    quarter = rect.width() * .25;
    half = rect.width() * .5;
    threequarters = rect.width() * .75;
    DrawParamsBuildTower *dps = (DrawParamsBuildTower*) dp;

    for (i = 0; i != ICON_MAX; i++) {
        iconDrawingHelper(resourcePixmapItemArray_[RESOURCE_WOOD][i],
                dps->pos.x(), dps->pos.y(),layer,i);
        resourcePixmapItemArray_[RESOURCE_WOOD][i]
            ->setPixmap(pixmapImgs_[PIX_BUILDING_TOWER_MAX]);

        iconDrawingHelper(resourcePixmapItemArray_[RESOURCE_STONE][i],
                dps->pos.x() + quarter, dps->pos.y(),layer,i);
        resourcePixmapItemArray_[RESOURCE_STONE][i]
            ->setPixmap(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 1]);

        iconDrawingHelper(resourcePixmapItemArray_[RESOURCE_BONE][i],
                dps->pos.x() + half, dps->pos.y(),layer,i);
        resourcePixmapItemArray_[RESOURCE_BONE][i]
            ->setPixmap(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 2]);

        iconDrawingHelper(resourcePixmapItemArray_[RESOURCE_TAR][i],
                dps->pos.x() + threequarters, dps->pos.y(),layer,i);
        resourcePixmapItemArray_[RESOURCE_TAR][i]
            ->setPixmap(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 3]);
        setIconVisibility(resourcePixmapItemArray_[RESOURCE_WOOD][i],
                i, dps->wood);
        setIconVisibility(resourcePixmapItemArray_[RESOURCE_STONE][i],
                i, dps->stone);
        setIconVisibility(resourcePixmapItemArray_[RESOURCE_TAR][i],
                i, dps->oil);
        setIconVisibility(resourcePixmapItemArray_[RESOURCE_BONE][i],
                i, dps->bone);
    }
    setBuildingGraphic(this->getPixmapItem());
    GraphicsComponent::draw(dp, layer - 1);
}

void BuildingTowerGraphicsComponent::iconDrawingHelper(
        QGraphicsPixmapItem *icon, int x, int y, int layer, int i) {

    int yoffset = getPixmapItem()->boundingRect().width() / 5;
    int center = getPixmapItem()->boundingRect().center().x();
    icon->setPos(x - center, y + i * yoffset - center);
    icon->setZValue(layer);
    icon->setScale(.6);
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
        return;
    }
    tower->resetDirty();

    DrawParamsBuildTower* dps = new DrawParamsBuildTower();
    dps->pos     = tower->getPos();
    dps->moving  = 0;
    dps->scale   = 1;
    dps->degrees = 0;
    dps->bone = tower->getBone();
    dps->oil = tower->getOil();
    dps->stone = tower->getStone();
    dps->wood = tower->getWood();
    dps->pixmapIdx = tower->evaluateBuildingStage();
    emit signalDraw(dps, this, LAYER_TOWER);
}

void BuildingTowerGraphicsComponent::setIconImages() {
    int i, j;
    for (i = 0; i != ICON_MAX; i++) {
        resourcePixmapItemArray_[RESOURCE_WOOD][i] = new
            QGraphicsPixmapItem(pixmapImgs_[PIX_BUILDING_TOWER_MAX]);
        resourcePixmapItemArray_[RESOURCE_WOOD][i]->setVisible(false);

        resourcePixmapItemArray_[RESOURCE_STONE][i] = new
            QGraphicsPixmapItem(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 1]);
        resourcePixmapItemArray_[RESOURCE_STONE][i]->setVisible(false);
        
        resourcePixmapItemArray_[RESOURCE_BONE][i] = new
            QGraphicsPixmapItem(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 2]);
        resourcePixmapItemArray_[RESOURCE_BONE][i]->setVisible(false);
        
        resourcePixmapItemArray_[RESOURCE_TAR][i] = new
            QGraphicsPixmapItem(pixmapImgs_[PIX_BUILDING_TOWER_MAX + 3]);
        resourcePixmapItemArray_[RESOURCE_TAR][i]->setVisible(false);
    }
    for (i = 0; i != ICON_MAX; i++) {
        for (j = 0; j != RESOURCE_TYPE_MAX; j++) {
            CDriver::instance()->getMainWindow()->getScene()
                ->addItem(resourcePixmapItemArray_[j][i]);
        }
    }
}

void BuildingTowerGraphicsComponent::setIconVisibility(
        QGraphicsPixmapItem *iconGraphic, int index, int resourceReq) {
    if (index < resourceReq) {
        iconGraphic->setVisible(true);
    } else {
        iconGraphic->setVisible(false);
    }
}

void BuildingTowerGraphicsComponent::setBuildingGraphic(QGraphicsPixmapItem * gpi) {
    gpi->setPixmap(pixmapImgs_[buildingStage_]);
}

} /* end namespace td */

