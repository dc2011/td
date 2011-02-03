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

#define TD_PORT 26631

namespace td
{

class NetworkClient : public QObject {
    Q_OBJECT

private:

    /**
     * The static singleton instance of the NetworkClient.
     *
     * It should only be retrieved using the instance() method, which
     * will initialize it the first time that it is retrieved.
     */
    static NetworkClient* instance_;
    
    /**
     * A Mutex to protect instance data from multiple threads.
     *
     * This must be used any time instance data is read or updated,
     * as well as when the singleton object is checked and initialized.
     *
     * This is static because it needs to be used in the instance()
     * method.
     */
    static QMutex mutex_;

    static QThread* netthread_;
    
    /**
     * Server Address
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
    explicit NetworkClient(QHostAddress servAddr);
    ~NetworkClient();
 
signals:
    void msgQueued();

private slots:
    void onMsgQueued();
    void onTCPReceive();
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
        mutex_.lock();
        msgQueue_.enqueue(msg);
        mutex_.unlock();

        emit msgQueued();
    }
};

} /*End of namespace*/


#endif
