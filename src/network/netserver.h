#ifndef _netserver_
#define _netserver_

#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
#include <QtDebug>
#include <QByteArray>
#include <QHostAddress>
#include <QtConcurrentRun>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QQueue>
#include "netmessages.h"
#include "stream.h"
#include "../util/defines.h"
#include "../util/mutex_magic.h"

namespace td
{

class NetworkServer : public QObject {
    Q_OBJECT
    THREAD_SAFE_CLASS

private:
    /**
     * The last digit of the next multicast address.
     */
    static unsigned char nextMulticast;

    /**
     * The thread which owns the NetworkServer and its sockets.
     */
    QThread* netthread_;

    /**
     * A QQueue for all the messages to be sent
     */
    QQueue<QByteArray> msgQueue_; 

    /**
     * A list of all the TCP connections.
     */
    QList<QTcpSocket*> tcpSockets_;
     
    /**
     * The udpSocket listening on the server.
     */
    QUdpSocket* udpSocket_;

    /**
     * The last digit of the multicast address for the server.
     */
    unsigned char multicastAddr_;

    /**
     * Indicates that the server should shut down when the queue is empty.
     */
    bool shuttingDown_;

public:
    /**
     * Constructor for the server-side networking singleton.
     *
     * @author Darryl Pogue
     */
    explicit NetworkServer();

    /**
     * Destructor for the network server, closes any open sockets.
     *
     * @author Darryl Pogue
     */
    virtual ~NetworkServer();

signals:
    /**
     * Signal emitted when a message is added to the message queue.
     * This is used to notify another thread that it should read a message
     * from the queue and send it across the network.
     * This signal should not be used outside of this class.
     */
    void msgQueued();

    /**
     * Signal emitted when a packet is read from UDP.
     * This is used to notify the driver that a packet has been received.
     */
    void msgReceived(Stream* s);

    /**
     * Signal emitted when there are no more connections to the server.
     */
    void disconnected();

    /**
     * Signal emitted when a socket disconnects.
     */
    void socketDisconnect(QTcpSocket* sock);

private slots:
    /**
     * Called when a message is queued to be sent, sends the message using 
     * the appropriate socket.
     *
     * @author Darryl Pogue
     * @author Terence Stenvold
     */
    void onMsgQueued();

    /**
     * Called when data is received by the TCP socket, parses the data and
     * distributes it to the correct object.
     *
     * @author Kelvin Lui
     * @author Darryl Pogue
     */
    void onTCPReceive();

    /**
     * Called when data is received by the UDP socket, parses the data and
     * distributes it to the correct object.
     *
     * @author Kelvin Lui
     * @author Darryl Pogue
     */
    void onUDPReceive();

    /**
     * Called when a connected client disconnects.
     *
     * @author Kelvin Lui
     */
    void onClientDisconnect();

public:
    /**
     * Starts the network server listening for data transmission.
     *
     * @author Darryl Pogue
     */
    void start();

    /**
     * Close the network sockets and empty the message buffer queue.
     * This should only be called once, when the program is exiting.
     *
     * @author Darryl Pogue
     */
    void shutdown();

    /** 
     * Send the ByteArray to the connected clients.
     * This adds the msg to be sent into a Queue, meaning it will be sent
     * as soon as it can be, but it doesn't block. The actual data sending
     * happens almost immediately in another thread.
     *
     * @author Terence Stenvold
     * @param msgType The type of message to be sent. (See netmessages.h)
     * @param msg The message data as a byte array.
     */
    void send(unsigned char msgType, QByteArray msg);

    /**
     * Adds the specified socket to the list of connected sockets.
     *
     * @author Darryl Pogue
     * @param conn The socket connection to be added.
     */
    void addConnection(QTcpSocket* conn) {
        connect(conn, SIGNAL(readyRead()), this, SLOT(onTCPReceive()));

        SAFE_OPERATION(tcpSockets_.append(conn))
    }

    /**
     * Returns the last digit of the server's multicast address.
     *
     * @author Darryl Pogue
     * @return The final multicast address octet.
     */
    unsigned char getMulticastAddr() {
        if (multicastAddr_ == 0) {
            multicastAddr_ = nextMulticast++;
        }
        return multicastAddr_;
    }
};

} /*End of namespace*/


#endif
