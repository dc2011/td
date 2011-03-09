#include "lobbyserver.h"
#include "stream.h"
#include "netmessages.h"

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

void LobbyServer::notifyClients(unsigned char msgType)
{
    switch (msgType) {
        case network::kLobbyWelcome:
        {
            Stream s;
            s.writeByte(msgType);
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

    connect(conn, SIGNAL(readyRead()),
            this, SLOT(readSocket()));
    connect(conn, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    clients_.append(conn);
}

void LobbyServer::readSocket()
{
    QTcpSocket* conn = (QTcpSocket*)QObject::sender();

    QByteArray data = conn->readAll();
    Stream s(data);

    unsigned char msgType = s.readByte();

    switch (msgType) {
        case network::kLobbyWelcome:
        {
            short version = s.readShort();
            if (version != 0x0001) {
                Stream rs;
                rs.writeByte(network::kBadVersion);
                conn->write(rs.data());
                conn->close();
                return;
            }

            int len = s.readByte();
            QString nick = QString(s.read(len));
            SAFE_OPERATION(connCount_++)
            notifyClients(network::kLobbyWelcome);
            qDebug() << "Number of clients connected = " << connCount_;
            break;
        }
    }
}

void LobbyServer::disconnected()
{
    QTcpSocket* conn = (QTcpSocket*)QObject::sender();

    clients_.removeOne(conn);

    SAFE_OPERATION(int count = connCount_)
    if (count > 0) {
        SAFE_OPERATION(connCount_--)
    }

    notifyClients(network::kLobbyWelcome);
    qDebug() << "Number of clients connected = " << connCount_;
}

} /* end namespace td */
