#ifndef GAMEINFO_H
#define GAMEINFO_H
#include <QtGui>
#include <QWidget>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include "GameMap.h"
class GameInfo {

private:
    //gameproperties, map, players etc
    GameMap map;
public:
   virtual GameInfo();
   virtual ~GameInfo();


};

#endif // GAMEINFO_H
