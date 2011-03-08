#include "lobbyserver.h"
#include "stream.h"

namespace td {

LobbyServer::LobbyServer(QObject* parent) : QObject(parent), connCount_(0)
{
    tcpServer_ = new QTcpServer();
    tcpServer_->listen(QHostAddress::Any, 26631);

    qDebug() << "Server is listening for connections";

    connect(tcpServer_, SIGNAL(newConnection()),
            this, SLOT(handleNewConnection()));
}

LobbyServer::~LobbyServer()
{
    delete tcpServer_;
}

void LobbyServer::notifyClients(int msgType)
{
    switch (msgType) {
        case kUpdateNumberOfClients:
        {
            Stream s;
            s.writeInt(msgType);
            SAFE_OPERATION(s.writeInt(connCount_))
            QByteArray data = s.data();
            foreach (QTcpSocket* sock, clients_) {
                sock->write(data);
                sock->flush();
            }
        }
    }
}

void LobbyServer::handleNewConnection()
{
    QTcpSocket* conn = tcpServer_->nextPendingConnection();
    if (conn == NULL) {
        return;
    }

    qDebug() << "Hi, I'm a server! Who are you?" <<
                conn->peerAddress().toString();

    connect(conn, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    clients_.append(conn);

    qDebug() << "Number of clients connected = " << clients_.size();

    SAFE_OPERATION(connCount_++)
    notifyClients(kUpdateNumberOfClients);
}

void LobbyServer::disconnected()
{
    QTcpSocket* conn = (QTcpSocket*)QObject::sender();

    clients_.removeOne(conn);

    qDebug() << "Number of clients connected = " << clients_.size();

    SAFE_OPERATION(connCount_--)
    notifyClients(kUpdateNumberOfClients);
}

} /* end namespace td */
