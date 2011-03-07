#ifndef SDRIVER_H
#define SDRIVER_H

#include <QTimer>
#include <QApplication>
#include <QObject>
#include <QVector>
#include <QMap>
#include <QHostAddress>
#include "ResManager.h"
#include "Player.h"
#include "../network/netserver.h"
#include "../network/stream.h"

namespace td {

class SDriver : public QObject {
    Q_OBJECT 

private:
    QTimer* gameTimer_;
    ResManager* mgr_;

public:
    // ctors and dtors
    SDriver();
    virtual ~SDriver();

    /**
     * Starts game timer, initializes network server instance,
     * also connects the onUDPReceived signal to UDPReceived slot.
     * 
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void startGame();

    /**
     * Stop game timer, and shuts down the network server.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void endGame();

    GameObject* updateObject(Stream* s);

public slots:
    /**
     * Handles a UDP packet receive by updating a currently existing player
     * or adding the player to the players list if the player does not exist.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void onUDPReceive(Stream* s);
};

} /* end namespace td */

#endif
