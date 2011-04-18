#include "netserver.h"
#include "../util/thread.h"

namespace td {

unsigned char NetworkServer::nextMulticast = 1;
unsigned char NetworkServer::portOffset = 0;

NetworkServer::NetworkServer()
{
    netthread_ = new Thread();
    udpSocket_ = new QUdpSocket();
    multicastAddr_ = 0;
    shuttingDown_ = false;

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
    udpPort_ = TD_PORT + portOffset++;
    udpSocket_->bind(udpPort_, QUdpSocket::ShareAddress);
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
    SAFE_OPERATION(shuttingDown_ = true);
}

void NetworkServer::send(unsigned char msgType, QByteArray msg) {
    SAFE_OPERATION(bool b = shuttingDown_)
    if (b) {
        /* Don't add more messages if we're shutting down. */
        return;
    }
    SAFE_OPERATION(msgQueue_.enqueue(msg.prepend(msgType)))

    emit msgQueued();
}

void NetworkServer::onMsgQueued()
{
    SAFE_OPERATION(QByteArray tmp = msgQueue_.dequeue())

    bool isUDP = ((unsigned char)tmp.at(0) >= td::network::kBLOCK_UDP);

    if (isUDP && multicastAddr_) {
        udpSocket_->writeDatagram(tmp, TD_GROUP(multicastAddr_), udpPort_);
    } else if (isUDP) {
        foreach (QTcpSocket* sock, tcpSockets_) {
            udpSocket_->writeDatagram(tmp, sock->peerAddress(), udpPort_);
        }
    } else {
        foreach (QTcpSocket* sock, tcpSockets_) {
            sock->write(tmp);
            sock->flush();
        }
    }

    mutex_.lock();
    bool b = shuttingDown_;
    int count = msgQueue_.size();
    mutex_.unlock();

    if (b && count == 0) {
        netthread_->exit(0);
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
    } else {
        emit socketDisconnect(sock);
    }
}

} /* end namespace td */
