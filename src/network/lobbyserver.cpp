#include "lobbyserver.h"
#include "stream.h"
#include "netmessages.h"
#include "../engine/SDriver.h"
#include <QCoreApplication>
#include <QDir>

namespace td {

LobbyServer* LobbyServer::instance_ = NULL;
QMutex LobbyServer::mutex_;

LobbyServer::LobbyServer(QObject* parent) : QTcpServer(parent), connCount_(0),gameId(1)
{
    this->listen(QHostAddress::Any, TD_PORT);
    qDebug() << "Server is listening for connections";

    QDir dir("maps");
    QStringList filters;
    filters << "*.nfo";
    maps_ = dir.entryList(filters, QDir::Readable | QDir::Files, QDir::Name);

    SAFE_OPERATION(instance_ = this)
}

LobbyServer::~LobbyServer()
{
    SAFE_OPERATION(instance_ = NULL)
}

void LobbyServer::signout(QString nickname) {
    SAFE_OPERATION(usernames_.remove(nickname))
}

void LobbyServer::notifyClients(unsigned char msgType,int gameId)
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
            QList<int> gameNames = games_.keys();
            s.writeByte(msgType);
            s.writeInt(clients_.size());
            foreach(QString name, clients_) {
                s.writeInt(name.size());
                s.write(name.toAscii());
                s.writeInt(games_.key(clients_.key(name)));

            }
            foreach (QTcpSocket* sock, clients_.keys()) {
                sock->write(s.data());
                sock->flush();
            }
            break;

        }
        case network::kUpdateListOfGames:
        {
            Stream s;

            QSet<int> gameNames = games_.keys().toSet();
            s.writeByte(msgType);
            s.writeInt(gameNames.size());
            foreach(int name, gameNames) {
                s.writeInt(name);
                s.writeInt(games_.count(name));
                foreach(QTcpSocket* sock,games_.values(name)) {
                    QString name = clients_.value(sock);
                    s.writeInt(name.size());
                    s.write(name.toAscii());
                }
            }
            foreach (QTcpSocket* sock, clients_.keys()) {
                sock->write(s.data());
                sock->flush();
            }
            break;
        }

        case network::kLobbyStartGame:
        {
            Stream s;
            s.writeByte(msgType);

            QString mapname(gameMaps_.value(gameId));
            s.writeInt(mapname.size());
            s.write(mapname.toAscii());

            QByteArray data = s.data();
            foreach (QTcpSocket* sock, games_.values(gameId)) {
                sock->write(data);
                sock->flush();
            }
            break;
        }
    }
}

void LobbyServer::startGame(int game) {
    notifyClients(network::kLobbyStartGame,game);

    Thread* gamethread = new Thread();
    SDriver* sd = new SDriver();
    connect(this, SIGNAL(startingGame(bool)), sd, SLOT(startGame(bool)));
    connect(sd, SIGNAL(disconnecting()), gamethread, SLOT(quit()));
    connect(sd, SIGNAL(disconnecting()), this, SLOT(gameEnd()));

    QString mapname = gameMaps_[game];
    sd->setMap(mapname);

    mutex_.lock();
    foreach (QTcpSocket* conn, games_.values(game)) {
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
        clients_.remove(conn);
    }

    games_.remove(game);
    gameMaps_.remove(game);
    mutex_.unlock();

    sd->initNetworking();
    sd->moveToThread(gamethread);
    gamethread->start();
    emit startingGame(false);
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
            if(usernames_.contains(nick)) {
                Stream error;
                QString msg("Username is already in use. Please Select a different one and try connecting again.");
                error.writeByte(network::kServerErrorMsg);
                error.writeInt(msg.size());
                error.write(msg.toAscii());
                conn->write(error.data());
                return;
            }
            connCount_++;
            mutex_.lock();
            usernames_.insert(nick);
            clients_.insert(conn, nick);
            mutex_.unlock();

            /* Send the list of maps */
            Stream rs;
            rs.writeByte(network::kMapList);
            rs.writeByte(maps_.size());
            foreach (QString str, maps_) {
                rs.writeByte(str.size());
                rs.write(str.toAscii().data());
            }
            conn->write(rs.data());

            notifyClients(network::kLobbyWelcome,0);
            notifyClients(network::kUpdateUserList,0);
            if(games_.size() > 0) {
                notifyClients(network::kUpdateListOfGames,0);
            }
            qDebug() << "Number of clients connected = " << connCount_;
            break;
        }
        case network::kJoinGame:
        {
            int len = s.readInt();
            QString nick = QString(s.read(len));
            int game = s.readInt();

            if(game == 0) {
                int len = s.readByte();
                QString name(s.read(len));

                Stream rs;
                rs.writeByte(network::kGameId);
                rs.writeInt(gameId);
                gameMaps_.insert(gameId, name);
                games_.insert(gameId++,conn);
                notifyClients(network::kUpdateListOfGames,0);
                conn->write(rs.data());
            }
            else {
                games_.insert(game,conn);
            }
            notifyClients(network::kUpdateListOfGames,0);
            notifyClients(network::kUpdateUserList,0);
            break;
        }
        case network::kLobbyleaveGame:
        {
            int nameLen = s.readInt();
            QString name(s.read(nameLen));
            int gameNum = s.readInt();
            games_.remove(gameNum,clients_.key(name));
            notifyClients(network::kUpdateUserList,0);
            notifyClients(network::kUpdateListOfGames,0);
            break;
        }

        case network::kLobbyStartGame:
        {
            int game = s.readInt();
            //int mapNameLen = s.readInt();
          //  QString mapName(s.read(mapNameLen));
            startGame(game);
            break;
        }
        case network::kChatMessage:
        {
            int nameLen = s.readInt();
            QString nickName(s.read(nameLen));
            int msgLen = s.readInt();
            QString msg(s.read(msgLen));
            relayChatMessage(nickName,msg);
            break;
        }
    }
}
void LobbyServer::relayChatMessage(QString& nickName, QString& msg) {
    Stream data;
    data.writeByte(network::kChatMessage);
    data.writeInt(nickName.size());
    data.write(nickName.toAscii());
    data.writeInt(msg.size());
    data.write(msg.toAscii());

    foreach(QTcpSocket* sock, clients_.keys()) {
       // if(nickName != clients_.value(sock)) {
            sock->write(data.data());
            sock->flush();
       // }
    }
}

void LobbyServer::disconnected()
{
    QTcpSocket* conn = (QTcpSocket*)QObject::sender();

    mutex_.lock();
    QString nick = clients_[conn];
    if (!nick.isEmpty()) {

        games_.remove(games_.key(conn),conn);

        clients_.remove(conn);
        connCount_ = (connCount_ > 0) ? connCount_ - 1 : 0;
        usernames_.remove(nick);
    }
    mutex_.unlock();

    notifyClients(network::kLobbyWelcome,0);
    notifyClients(network::kUpdateUserList,0);
    notifyClients(network::kUpdateListOfGames,0);
    qDebug() << "Number of clients connected = " << connCount_;
}

void LobbyServer::gameEnd() {
    SDriver* sd = (SDriver*)QObject::sender();

    qDebug("Game Server shutting down");
    delete sd;
}

} /* end namespace td */
