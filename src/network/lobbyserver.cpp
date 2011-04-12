#include "lobbyserver.h"
#include "stream.h"
#include "netmessages.h"
#include "../engine/SDriver.h"
#include <QCoreApplication>

namespace td {

LobbyServer* LobbyServer::instance_ = NULL;
QMutex LobbyServer::mutex_;

LobbyServer::LobbyServer(QObject* parent) : QTcpServer(parent), connCount_(0)
{
    this->listen(QHostAddress::Any, TD_PORT);
    qDebug() << "Server is listening for connections";

    SAFE_OPERATION(instance_ = this)
}

LobbyServer::~LobbyServer()
{
    SAFE_OPERATION(instance_ = NULL)
}

void LobbyServer::signout(QString nickname) {
    SAFE_OPERATION(usernames_.remove(nickname))
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
            foreach (QTcpSocket* sock, clients_.keys()) {
                sock->write(data);
                sock->flush();
            }
            break;
        }
        case network::kUpdateUserList:
        {
            Stream s;
            s.writeByte(msgType);
            s.writeInt(usernames_.size());
            foreach (QString name, usernames_) {
                s.writeInt(name.size());
                s.write(name.toAscii().data());

            }
            foreach (QTcpSocket* sock, clients_.keys()) {
                sock->write(s.data());
                sock->flush();
            }

        }
        case network::kUpdateListOfGames:
            
        case network::kBadVersion:
        case network::kLobbyStartGame:
        {
            Stream s;
            s.writeByte(msgType);
            QByteArray data = s.data();
            foreach (QTcpSocket* sock, clients_.keys()) {
                sock->write(data);
                sock->flush();
            }
            break;
        }
    }
}

void LobbyServer::startGame() {
    notifyClients(network::kLobbyStartGame);

    Thread* gamethread = new Thread();
    SDriver* sd = new SDriver();
    connect(this, SIGNAL(startingGame()), sd, SLOT(startGame()));
    connect(sd, SIGNAL(disconnecting()), gamethread, SLOT(quit()));
    connect(sd, SIGNAL(disconnecting()), this, SLOT(gameEnd()));

    mutex_.lock();
    foreach (QTcpSocket* conn, clients_.keys()) {
        disconnect(conn, SIGNAL(readyRead()),
                    this, SLOT(readSocket()));
        disconnect(conn, SIGNAL(disconnected()),
                    this, SLOT(disconnected()));

        QString nick = clients_[conn];
        unsigned int id = sd->addPlayer(conn, nick);

        Stream s;
        s.writeByte(network::kAssignPlayerID);
        s.writeInt(id);

        conn->write(s.data());
    }
    clients_.clear();
    connCount_ = 0;
    mutex_.unlock();

    sd->initNetworking();
    sd->moveToThread(gamethread);
    gamethread->start();
    emit startingGame();
}

void LobbyServer::incomingConnection(int socketDescriptor)
{
    QTcpSocket* conn = new QTcpSocket();
    conn->setSocketDescriptor(socketDescriptor);
    conn->setSocketOption(QAbstractSocket::LowDelayOption, true);

    qDebug() << "Hi, I'm a server! Who are you?" <<
                conn->peerAddress().toString();

    connect(conn, SIGNAL(readyRead()),
            this, SLOT(readSocket()));
    connect(conn, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
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
            if (version != TD_VERSION) {
                Stream rs;
                rs.writeByte(network::kBadVersion);
                conn->write(rs.data());
                conn->close();
                return;
            }

            int len = s.readByte();
            QString nick = QString(s.read(len));

            mutex_.lock();
            connCount_++;
            usernames_.insert(nick);
            clients_.insert(conn, nick);
            mutex_.unlock();

            notifyClients(network::kLobbyWelcome);
            notifyClients(network::kUpdateUserList);
            qDebug() << "Number of clients connected = " << connCount_;
            break;
        }
        case network::kLobbyStartGame:
        {
            startGame();
            /*foreach (QTcpSocket* sock, clients_) {
                disconnect(sock, SIGNAL(readyRead()),
                        this, SLOT(readSocket()));
            }
            qDebug() << "Starting a game...";

            // Here we should be forking
            int pid = fork();
            qDebug() << "PID is" << pid;
            if (pid == 0) {
                disconnect(tcpServer_, SIGNAL(newConnection()),
                        this, SLOT(handleNewConnection()));
                tcpServer_->close();
                qDebug() << "Exiting with code 1...";
                _exit(1);
            } else {
                mutex_.lock();
                connCount_ = 0;
                clients_.clear();

                foreach (QString nick, connections_.keys()) {
                    qDebug() << "Master has Nickname:" << nick;
                }
                mutex_.unlock();
            }*/
            break;
        }
    }
}

void LobbyServer::disconnected()
{
    QTcpSocket* conn = (QTcpSocket*)QObject::sender();

    mutex_.lock();
    QString nick = clients_[conn];
    if (!nick.isEmpty()) {
        clients_.remove(conn);
        connCount_ = (connCount_ > 0) ? connCount_ - 1 : 0;
        usernames_.remove(nick);
    }
    mutex_.unlock();

    notifyClients(network::kLobbyWelcome);
    notifyClients(network::kUpdateUserList);
    qDebug() << "Number of clients connected = " << connCount_;
}

void LobbyServer::gameEnd() {
    SDriver* sd = (SDriver*)QObject::sender();

    qDebug("Game Server shutting down");
    delete sd;
}

} /* end namespace td */
