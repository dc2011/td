#include "netclient.h"
#include "stream.h"
#include "../util/thread.h"
//#include <ctime>


namespace td {

NetworkClient* NetworkClient::instance_ = NULL;
QMutex NetworkClient::mutex_;
QThread* NetworkClient::netthread_ = NULL;

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

    netthread_ = new Thread();

    instance_->moveToThread(netthread_);
    instance_->udpSocket_->moveToThread(netthread_);
    instance_->tcpSocket_->moveToThread(netthread_);

    netthread_->start();

    return instance_;
}

void NetworkClient::shutdown() {
    mutex_.lock();
    delete instance_;
    instance_ = NULL;
    mutex_.unlock();

    netthread_->exit(0);
}

void NetworkClient::onMsgQueued()
{
    mutex_.lock();
    QByteArray tmp = msgQueue_.dequeue();
    mutex_.unlock();

    /* TODO: Determine which socket to use based on message type */
    udpSocket_->writeDatagram(tmp, tmp.size(), QHostAddress::Broadcast, TD_PORT);
}

void NetworkClient::onUDPReceive()
{
    QByteArray datagram;
    datagram.resize(udpSocket_->pendingDatagramSize());
    udpSocket_->readDatagram(datagram.data(), datagram.size());

    Stream s(datagram);
    /* TODO: Give the stream to an object */
}

void NetworkClient::onTCPReceive()
{
    /* TODO */
}

} /* End of namespace */
