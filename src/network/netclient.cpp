#include "netclient.h"
#include <ctime>


namespace td {

NetworkClient* NetworkClient::instance_ = NULL;
QMutex NetworkClient::mutex_;

NetworkClient::NetworkClient(QHostAddress servAddr)
    : serverAddr_(servAddr)
{
    tcpSocket_ = new QTcpSocket();
    tcpSocket_->connectToHost(servAddr, TD_PORT);

    udpSocket_ = new QUdpSocket();

    connect(this, SIGNAL(msgQueued()), this, SLOT(onMsgQueued()),
            Qt::QueuedConnection);
    connect(tcpSocket_, SIGNAL(readyRead()), this, SLOT(onTCPReceive()));
    connect(udpSocket_, SIGNAL(readyRead()), this, SLOT(onUDPReceive()));
}

NetworkClient::~NetworkClient()
{
    mutex_.lock();
    /* No cleanup for udpSocket_? */

    if (tcpSocket_->isOpen()) {
        tcpSocket_->disconnectFromHost();
        tcpSocket_->waitForDisconnected(1000);
    }

    msgQueue_.clear();
    mutex_.unlock();
}

NetworkClient* NetworkClient::init(QHostAddress servAddr)
{
    if (instance_ != NULL) {
        return instance_;
    }

    mutex_.lock();
    instance_ = new NetworkClient(servAddr);
    mutex_.unlock();

    return instance_;
}

void NetworkClient::onMsgQueued()
{
    mutex_.lock();
    QByteArray tmp = msgQueue_.dequeue();
    mutex_.unlock();

    /* TODO: Determine which socket to use based on message type */
    udpSocket_->writeDatagram(tmp, tmp.size(), serverAddr_, TD_PORT);
}

void NetworkClient::onUDPReceive()
{
    /* TODO */
}

void NetworkClient::onTCPReceive()
{
    /* TODO */
}

} /* End of namespace */
