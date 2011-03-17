#include "netserver.h"
#include "../util/thread.h"

namespace td {

NetworkServer::NetworkServer()
{
    netthread_ = new Thread();
    udpSocket_ = new QUdpSocket();

    connect(this, SIGNAL(msgQueued()), this, SLOT(onMsgQueued()),
            Qt::QueuedConnection);
    connect(udpSocket_, SIGNAL(readyRead()), this, SLOT(onUDPReceive()));
}

NetworkServer::~NetworkServer()
{
    delete udpSocket_;

    msgQueue_.clear();
}

void NetworkServer::start()
{
    udpSocket_->bind(TD_PORT, QUdpSocket::ShareAddress);
    udpSocket_->moveToThread(netthread_);

    foreach (QTcpSocket* sock, tcpSockets_) {
        sock->moveToThread(netthread_);
    }

    this->moveToThread(netthread_);
    netthread_->start();
}

void NetworkServer::shutdown()
{
    netthread_->exit(0);
}

void NetworkServer::onMsgQueued()
{
    SAFE_OPERATION(QByteArray tmp = msgQueue_.dequeue())

    bool isUDP = ((unsigned char)tmp.at(0) >= td::network::kBLOCK_UDP);

    if (isUDP) {
        udpSocket_->writeDatagram(tmp, TD_GROUP, TD_PORT);
    } else {
        foreach (QTcpSocket* sock, tcpSockets_) {
            sock->write(tmp);
        }
    }
}

void NetworkServer::onTCPReceive()
{
    QTcpSocket* sock = (QTcpSocket*)QObject::sender();
    QByteArray data = sock->readAll();
    Stream* s = new Stream(data);

    emit msgReceived(s);
}

void NetworkServer::onUDPReceive()
{
    QByteArray datagram;
    datagram.resize(udpSocket_->pendingDatagramSize());
    udpSocket_->readDatagram(datagram.data(), datagram.size());
    Stream* s = new Stream(datagram);

    emit msgReceived(s);
}

} /* end namespace td */
