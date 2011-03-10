#include "MapDisplayer.h"

#include "isometricrenderer.h"
#include "map.h"
#include "mapobject.h"
#include "mapreader.h"
#include "objectgroup.h"
#include "orthogonalrenderer.h"
#include "tilelayer.h"
#include "tileset.h"
#include "tile.h"

#include <QCoreApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

using namespace Tiled;

/**
 * Item that represents a map object.
 */
class MapObjectItem : public QGraphicsItem {
public:
    MapObjectItem(MapObject* mapObject, MapRenderer* renderer,
                  QGraphicsItem* parent = 0)
        : QGraphicsItem(parent)
        , mMapObject(mapObject)
        , mRenderer(renderer)
    {}

    QRectF boundingRect() const {
        return mRenderer->boundingRect(mMapObject);
    }

    void paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
        const QColor& color = mMapObject->objectGroup()->color();
        mRenderer->drawMapObject(p, mMapObject,
                                 color.isValid() ? color : Qt::darkGray);
    }

private:
    MapObject* mMapObject;
    MapRenderer* mRenderer;
};

/**
 * Item that represents a tile layer.
 */
class TileLayerItem : public QGraphicsItem {
public:
    TileLayerItem(TileLayer* tileLayer, MapRenderer* renderer,
                  QGraphicsItem* parent = 0)
        : QGraphicsItem(parent)
        , mTileLayer(tileLayer)
        , mRenderer(renderer) {
#if QT_VERSION >= 0x040600
        setFlag(QGraphicsItem::ItemUsesExtendedStyleOption);
#endif

        //qDebug() << tileLayer->height();
        //for (int i = 0; i < tileLayer->width(); i++) {
        //  for (int j = 0; j < tileLayer->height(); j++) {
        //    qDebug() << "x:" << i << "y:" << j << "tile: " << tileLayer->tileAt(i, j)->id();
        //  }
        //}
    }

    QRectF boundingRect() const {
        return mRenderer->boundingRect(mTileLayer->bounds());
    }

    void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget*) {
        mRenderer->drawTileLayer(p, mTileLayer, option->rect);
    }

private:
    TileLayer* mTileLayer;
    MapRenderer* mRenderer;
};

/**
 * Item that represents an object group.
 */
class ObjectGroupItem : public QGraphicsItem {
public:
    ObjectGroupItem(ObjectGroup* objectGroup, MapRenderer* renderer,
                    QGraphicsItem* parent = 0)
        : QGraphicsItem(parent) {
#if QT_VERSION >= 0x040600
        setFlag(QGraphicsItem::ItemHasNoContents);
#endif
        // Create a child item for each object
        //qDebug() << "Map Tiles:";
        foreach(MapObject * object, objectGroup->objects()) {
          new MapObjectItem(object, renderer, this);
        }
    }

    QRectF boundingRect() const {
        return QRectF();
    }
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {}
};

/**
 * Item that represents a map.
 */
class MapItem : public QGraphicsItem {
public:
    MapItem(Map* map, MapRenderer* renderer, QGraphicsItem* parent = 0)
        : QGraphicsItem(parent) {
#if QT_VERSION >= 0x040600
        setFlag(QGraphicsItem::ItemHasNoContents);
#endif
        // Create a child item for each layer
        int i = 0;
        foreach(Layer * layer, map->layers()) {
            if (TileLayer* tileLayer = layer->asTileLayer()) {
                if (i < 2) { // only show the first 2 layers
                    new TileLayerItem(tileLayer, renderer, this);
                    i++;
                }
            } else if (ObjectGroup* objectGroup = layer->asObjectGroup()) {
                // uncomment this line to see the objects again
                //new ObjectGroupItem(objectGroup, renderer, this);
            }
        }
    }

    QRectF boundingRect() const {
        return QRectF();
    }
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {}
};


td::MapDisplayer::MapDisplayer(QGraphicsScene* scene, QWidget* parent) :
    QGraphicsView(parent),
    mScene(scene),
    mMap(0),
    mRenderer(0)
{
    setScene(mScene);
    setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing
                         | QGraphicsView::DontSavePainterState);
    setBackgroundBrush(Qt::black);
    setFrameStyle(QFrame::NoFrame);
    viewport()->setAttribute(Qt::WA_StaticContents);
}

td::MapDisplayer::~MapDisplayer()
{
    qDeleteAll(mMap->tilesets());
    delete mMap;
    delete mRenderer;
}

void td::MapDisplayer::viewMap(const QString& fileName)
{
    delete mRenderer;
    mRenderer = 0;
    mScene->clear();
    centerOn(0, 0);
    MapReader reader;
    mMap = reader.readMap(fileName);

    if (!mMap) {
        return;    // TODO: Add error handling
    }

    switch (mMap->orientation()) {
        case Map::Isometric:
            mRenderer = new IsometricRenderer(mMap);
            break;
        case Map::Orthogonal:
        default:
            mRenderer = new OrthogonalRenderer(mMap);
            break;
    }

    mScene->addItem(new MapItem(mMap, mRenderer));
}
