#ifndef _LOBBYSERVER_H
#define _LOBBYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMap>
#include <QMutex>
#include "../util/defines.h"
#include "../util/thread.h"
#include "../util/mutex_magic.h"

namespace td {

class LobbyServer : public QTcpServer
{
    Q_OBJECT
    THREAD_SAFE_SINGLETON

private:
    /**
     * The static singleton instance of the LobbyServer.
     *
     * It should only be retrieved using the instance() method, which
     * will initialize it the first time that it is retrieved.
     */
    static LobbyServer* instance_;

    unsigned int connCount_;

    /**
     * Map of the sockets currently waiting in the lobby, keyed by their sockets.
     * The value is the nickname of the player.
     */
    QMap<QTcpSocket*, QString> clients_;
     
    /**
     * Map of all the games. The key will be a incrementing id. The value will be their sockets which can be used to map
     * to their nickname
     */
    QMultiMap<int,QTcpSocket*> games_;
    
/**
     * Set of all currently used nicknames, to prevent multiple users with the
     * same nickname.
     */
    QSet<QString> usernames_;
    /** Id to use for the game*/
    int gameId;



public:
    explicit LobbyServer(QObject* parent = 0);
    virtual ~LobbyServer();

    /**
     * Return the instance of the LobbyServer.
     *
     * @author Darryl Pogue
     * @return A pointer to the LobbyServer instance.
     */
    static LobbyServer* instance() {
        return instance_;
    }

    /**
     * Removes a nickname from the set of names in use, allowing other players
     * to connect with this name.
     *
     * @author Darryl Pogue
     * @param nickname The nickname to be removed.
     */
    void signout(QString nickname);

protected:
    /**
     * Sends a message of the given type to all clients currently waiting in the
     * lobby.
     *
     * @author Kelvin Lui
     * @author Darryl Pogue
     * @param msgType The message type to be sent.
     */
    void notifyClients(unsigned char msgType);

    /**
     * Relays a message sent by a client to all other connected clients
     * @author Kelvin Lui
     * @param nickname the nickname to be prepended to the message
     * @param msg the message to be sent
     */
    void relayChatMessage(QString& nickName,QString& msg);
    void startGame(int);

    /**
     * Reimplement and override the default QTcpServer connection behaviour.
     *
     * @author Darryl Pogue
     * @param socketDescriptor The descriptor of the connected socket.
     */
    virtual void incomingConnection(int socketDescriptor);

signals:
    void startingGame();

private slots:
    void readSocket();
    void disconnected();
    void gameEnd();
};

} /* end namespace td */

#endif
