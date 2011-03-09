#ifndef TMXVIEWER_H
#define TMXVIEWER_H

#include <QString>
#include <QGraphicsView>

namespace Tiled {
class Map;
class MapRenderer;
}

namespace td {

class MapDisplayer : public QGraphicsView {
    Q_OBJECT

public:
    explicit MapDisplayer(QGraphicsScene* scene, QWidget* parent = 0);
    ~MapDisplayer();
    void viewMap(const QString& fileName);
    Tiled::Map* map() { return mMap; }
    Tiled::MapRenderer* getMRenderer() { return mRenderer; }

private:
    QGraphicsScene* mScene;
    Tiled::Map* mMap;
    Tiled::MapRenderer* mRenderer;
};

} // namespace td

