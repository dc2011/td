#ifndef TMXVIEWER_H
#define TMXVIEWER_H

#include <QGraphicsView>

namespace Tiled {
class Map;
class MapRenderer;
}

class MapDisplayer : public QGraphicsView {
    Q_OBJECT

public:
    explicit MapDisplayer(QGraphicsScene scene, QWidget* parent = 0);
    ~MapDisplayer();

    void viewMap(const QString& fileName);

private:
    QGraphicsScene* mScene;
    Tiled::Map* mMap;
    Tiled::MapRenderer* mRenderer;
};

#endif // TMXVIEWER_H
