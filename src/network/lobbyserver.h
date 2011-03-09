#ifndef _LOBBYSERVER_H
#define _LOBBYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMutex>
#include "../util/mutex_magic.h"

namespace td {

class LobbyServer : public QObject
{
    Q_OBJECT
    THREAD_SAFE_CLASS

private:
    QTcpServer* tcpServer_;
    unsigned int connCount_;
    QList<QTcpSocket*> clients_;

public:
    LobbyServer(QObject* parent = 0);
    virtual ~LobbyServer();

protected:
    void notifyClients(unsigned char msgType);

private slots:
    void handleNewConnection();
    void readSocket();
    void disconnected();

};

} /* end namespace td */

#endif
