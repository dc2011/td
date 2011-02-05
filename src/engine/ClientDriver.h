#ifndef CLIENTDRIVER_H
#define CLIENTDRIVER_H

#include <QApplication>
#include <QTimer>

#include "Player.h"

class ClientDriver : public QObject {
    Q_OBJECT
public:
    ClientDriver();
    ~ClientDriver();
    
    void Start();
    Player* CreateHumanPlayer();
    
private:
    QTimer* timer_;
    Player* player_;
};

#endif