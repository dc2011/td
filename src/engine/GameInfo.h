#ifndef GAMEINFO_H
#define GAMEINFO_H
#include <QtGui>
#include <QWidget>
#include <QTimer>
#include <QApplication>
#include <QVector>
//#include "GameMap.h"

namespace td{
class GameInfo : public QObject {
    Q_OBJECT

private:
    //gameproperties, map, players etc
   // GameMap map;
    enum difficulty {EASY = 0, MEDIUM = 1, HARD = 2, INSANE = 3};

public:
    GameInfo();
    ~GameInfo();


};
} /* end namespace td */
#endif // GAMEINFO_H
