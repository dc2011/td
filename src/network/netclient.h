#ifndef _netclient_
#define _netclient_

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
#include "../util/mutex_magic.h"

#define TD_PORT 26631

namespace td
{

/**
 * The client-side networking manager class.
 * This class is used to handle networking sending and receiving for both
 * TCP and UDP. A client must call the init() method first to create and 
 * initialize the singleton instance. Once a call to init has been made,
 * this class is thread-safe and the send method can be called from any
 * thread. The existing instance of the network client can be retrieved from
 * anywhere with a call to instance().
 *
 * Internally, when init is called, this class creates a thread in which 
 * all socket reading and writing is to be done. Thus this class is entirely
 * event-driven, and code wishing to push a message across the network
 * should do so by calling the send() method.
 *
 * A shutdown() method exists to close all open conenctions and destroy the
 * network client instance. This should only be called when the client is
 * exiting.
 *
 * A typical use of the NetworkClient class looks like this:
 * @code
 *  td::NetworkClient::init(QHostAddress("127.0.0.1"));
 *
 *  // Create a stream and write data to it, then send it to the server:
 *  td::Stream s;
 *  s.writeInt(5);
 *  td::NetworkClient::instance()->send(s.data());
 *
 *  // When the client is exiting:
 *  td::NetworkClient::instance()->shutdown();
 * @endcode
 *
 * @author Darryl Pogue
 * @author Terence Stenvold
 */
class NetworkClient : public QObject {
    Q_OBJECT

    THREAD_SAFE_SINGLETON

private:

    /**
     * The static singleton instance of the NetworkClient.
     *
     * It should only be retrieved using the instance() method, which
     * will initialize it the first time that it is retrieved.
     */
    static NetworkClient* instance_;

    /**
     * The thread which owns the NetworkClient and its sockets.
     */
    static QThread* netthread_;
    
    /**
     * The address of the network server.
     */
    QHostAddress serverAddr_;
     
    /**
     * A QQueue for all the messages to be sent
     */
    QQueue<QByteArray> msgQueue_; 

    /**
     * The tcpSocket to the server
     */         
    QTcpSocket* tcpSocket_;
     
    /**
     * The udpSocket to the server
     */
    QUdpSocket* udpSocket_;


private:
    /**
     * Constructor for the client-side networking singleton.
     *
     * @author Darryl Pogue
     * @param servAddr The address of the server.
     */
    explicit NetworkClient(QHostAddress servAddr);

    /**
     * Destructor for the network client, closes any open sockets.
     *
     * @author Darryl Pogue
     */
    virtual ~NetworkClient();
 
signals:
    /**
     * Signal emitted when a message is added to the message queue.
     * This is used to notify another thread that it should read a message
     * from the queue and send it across the network.
     * This signal should not be used outside of this class.
     */
    void msgQueued();

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
     * @author Darryl Pogue
     */
    void onTCPReceive();

    /**
     * Called when data is received by the UDP socket, parses the data and
     * distributes it to the correct object.
     *
     * @author Darryl Pogue
     */
    void onUDPReceive();
     
public:
    /**
     * Create and initialize the NetworkClient instance.
     * This must be the first NetworkClient function that is called. Once an
     * instance has been created, all calls to init() or instance() will
     * return the existing instance.
     *
     * @author Darryl Pogue
     * @param servAddr The address of the network server.
     * @return A pointer to the initialized NetworkClient instance.
     */
    static NetworkClient* init(QHostAddress servAddr);

    /**
     * Close the network sockets and empty the message buffer queue.
     * This should only be called once, when the program is exiting.
     *
     * @author Darryl Pogue
     */
    static void shutdown();

    /**
     * Return the instance of the NetworkClient.
     * You MUST call init() to create the initial instance. Once an instance
     * has been created, all calls to init() or instance() will return the
     * existing instance.
     *
     * @author Terence Stenvold
     * @author Darryl Pogue
     * @return A pointer to the NetworkClient instance.
     */
    static NetworkClient* instance() {
        return instance_;
    }
  
    /** 
     * Send the ByteArray to the server.
     * This adds the msg to be sent to the server into a Queue, meaning it
     * will be sent as soon as it can be, but it doesn't block. The actual
     * data sending happens almost immediately in another thread.
     *
     * @author Terence Stenvold
     * @param msg as a byteArray 
     */
    void send(const QByteArray& msg) {
        SAFE_OPERATION(msgQueue_.enqueue(msg))

        emit msgQueued();
    }
};

} /*End of namespace*/


#endif
