#ifndef TILE_H
#define TILE_H

#include <QObject>

class Tile : public QObject {
  Q_OBJECT
public:
  Tile(QObject *parent = 0) { }
  virtual ~Tile() { }

private:
  
};

#endif
