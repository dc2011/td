#include "netserver.h"
#include "../util/thread.h"

namespace td {

NetworkServer* NetworkServer::instance_ = NULL;
QMutex NetworkServer::mutex_;
QThread* NetworkServer::netthread_ = NULL;

NetworkServer::NetworkServer()
{
    udpSocket_ = new QUdpSocket();
    udpSocket_->bind(TD_PORT, QUdpSocket::ShareAddress);
    connect(this, SIGNAL(msgQueued()), this, SLOT(onMsgQueued()),
            Qt::QueuedConnection);
    connect(udpSocket_, SIGNAL(readyRead()), this, SLOT(onUDPReceive()));
}

NetworkServer::~NetworkServer()
{
    mutex_.lock();
    msgQueue_.clear();
    mutex_.unlock();
}

NetworkServer* NetworkServer::init()
{
    if (instance_ != NULL) {
        return instance_;
    }

    SAFE_OPERATION(instance_ = new NetworkServer())

    netthread_ = new Thread();
    instance_->moveToThread(netthread_);
    instance_->udpSocket_->moveToThread(netthread_);
    //instance_->tcpSocket_->moveToThread(netthread_);
    netthread_->start();
    return instance_;
}

void NetworkServer::shutdown()
{
    mutex_.lock();
    delete instance_;
    instance_ = NULL;
    mutex_.unlock();

    netthread_->exit(0);
}

void NetworkServer::onMsgQueued()
{
    SAFE_OPERATION(QByteArray tmp = msgQueue_.dequeue())

    bool isUDP = ((unsigned char)tmp.at(0) >= td::network::kBLOCK_UDP);

    if (isUDP) {
        udpSocket_->writeDatagram(tmp, QHostAddress::Broadcast, TD_PORT);
    } else {
        //tcpSocket_->write(tmp);
    }
}

void NetworkServer::onUDPReceive()
{
    QByteArray datagram;
    datagram.resize(udpSocket_->pendingDatagramSize());
    udpSocket_->readDatagram(datagram.data(), datagram.size());
    Stream* s = new Stream(datagram);

    emit UDPReceived(s);
}

} /* end namespace td */
