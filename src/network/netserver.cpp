#include "netserver.h"
#include "../util/thread.h"

namespace td {

unsigned char NetworkServer::nextMulticast = 1;

NetworkServer::NetworkServer()
{
    netthread_ = new Thread();
    udpSocket_ = new QUdpSocket();
    multicastAddr_ = 0;

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
        connect(sock, SIGNAL(disconnected()), this, SLOT(onClientDisconnect()));
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

    if (isUDP && multicastAddr_) {
        udpSocket_->writeDatagram(tmp, TD_GROUP(multicastAddr_), TD_PORT);
    } else if (isUDP) {
        foreach (QTcpSocket* sock, tcpSockets_) {
            udpSocket_->writeDatagram(tmp, sock->peerAddress(), TD_PORT);
        }
    } else {
        foreach (QTcpSocket* sock, tcpSockets_) {
            sock->write(tmp);
            sock->flush();
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
void NetworkServer::onClientDisconnect() {
    QTcpSocket* sock = (QTcpSocket*)QObject::sender();
    mutex_.lock();
    tcpSockets_.removeOne(sock);
    int count = tcpSockets_.size();
    mutex_.unlock();

    if (count == 0) {
        emit disconnected();
    }
}

} /* end namespace td */
