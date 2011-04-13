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
     * Set of all currently used nicknames, to prevent multiple users with the
     * same nickname.
     */
    QSet<QString> usernames_;

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

    void startGame();

    /**
     * Reimplement and override the default QTcpServer connection behaviour.
     *
     * @author Darryl Pogue
     * @param socketDescriptor The descriptor of the connected socket.
     */
    virtual void incomingConnection(int socketDescriptor);

signals:
    void startingGame(bool multicasting);

private slots:
    void readSocket();
    void disconnected();
    void gameEnd();
};

} /* end namespace td */

#endif
