#include "netclient.h"
#include "stream.h"
#include "../util/thread.h"

#if QT_VERSION < 0x040800
#  ifdef Q_WS_WIN
#    include <winsock2.h>
#    include <WS2tcpip.h>
#  else
#    include <sys/types.h>
#    include <sys/socket.h>
#    include <arpa/inet.h>
#  endif
#endif


namespace td {

NetworkClient* NetworkClient::instance_ = NULL;
QMutex NetworkClient::mutex_;
QThread* NetworkClient::netthread_ = NULL;

NetworkClient::NetworkClient(QHostAddress servAddr)
    : serverAddr_(servAddr), multicastAddr_(0)
{
    tcpSocket_ = new QTcpSocket();
    tcpSocket_->connectToHost(servAddr, TD_PORT);
    tcpSocket_->waitForConnected(1000);
    udpSocket_ = new QUdpSocket();

    connect(this, SIGNAL(msgQueued()), this, SLOT(onMsgQueued()),
            Qt::QueuedConnection);
    connect(this, SIGNAL(joinMulticast(unsigned char)),
            this, SLOT(onMulticastJoin(unsigned char)), Qt::QueuedConnection);
    connect(this, SIGNAL(startUDP(unsigned short)),
            this, SLOT(onConnectUDP(unsigned short)), Qt::QueuedConnection);
    connect(tcpSocket_, SIGNAL(readyRead()), this, SLOT(onTCPReceive()));
    connect(udpSocket_, SIGNAL(readyRead()), this, SLOT(onUDPReceive()));
}

NetworkClient::~NetworkClient()
{
    if (multicastAddr_) {
#if QT_VERSION >= 0x040800
        udpSocket_->leaveMulticastGroup(TD_GROUP(multicastAddr_));
#else
        int fd = udpSocket_->socketDescriptor();
        ip_mreq mreq;

        mreq.imr_multiaddr.s_addr = htonl(TD_GROUP(multicastAddr_).toIPv4Address());
        mreq.imr_interface.s_addr = htonl(INADDR_ANY);
        if (setsockopt(fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq))
                < 0) {
            perror("setsockopt");
        }
#endif
    }
    delete udpSocket_;

    if (tcpSocket_->isOpen()) {
        tcpSocket_->disconnectFromHost();
    }
    delete tcpSocket_;

    msgQueue_.clear();
}

NetworkClient* NetworkClient::init(QHostAddress servAddr)
{
    if (instance_ != NULL) {
        return instance_;
    }

    SAFE_OPERATION(instance_ = new NetworkClient(servAddr))

    netthread_ = new Thread();
    instance_->moveToThread(netthread_);
    instance_->udpSocket_->moveToThread(netthread_);
    instance_->tcpSocket_->moveToThread(netthread_);
    netthread_->start();
    return instance_;
}

void NetworkClient::shutdown()
{
    mutex_.lock();
    if (instance_ == NULL) {
        mutex_.unlock();
        return;
    }
    delete instance_;
    instance_ = NULL;
    mutex_.unlock();

    netthread_->exit(0);
}

void NetworkClient::onMsgQueued()
{
    SAFE_OPERATION(QByteArray tmp = msgQueue_.dequeue())

    bool isUDP = ((unsigned char)tmp.at(0) >= td::network::kBLOCK_UDP);

    if (isUDP) {
        udpSocket_->writeDatagram(tmp, serverAddr_, port_);
    } else {
        tcpSocket_->write(tmp);
    }
}

bool NetworkClient::isConnected() {
    return tcpSocket_->state() == QAbstractSocket::ConnectedState;
}

void NetworkClient::onMulticastJoin(unsigned char digit) {
    multicastAddr_ = digit;

#if QT_VERSION >= 0x040800
    udpSocket_->joinMulticastGroup(TD_GROUP(multicastAddr_));
#else
    int fd = udpSocket_->socketDescriptor();
    ip_mreq mreq;

    mreq.imr_multiaddr.s_addr = htonl(TD_GROUP(multicastAddr_).toIPv4Address());
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq))
            < 0) {
        perror("setsockopt");
    }
#endif
}

void NetworkClient::onConnectUDP(unsigned short port) {
    port_ = port;
    udpSocket_->bind(port, QUdpSocket::ShareAddress);
}

void NetworkClient::onUDPReceive()
{
    QByteArray datagram;
    datagram.resize(udpSocket_->pendingDatagramSize());
    udpSocket_->readDatagram(datagram.data(), datagram.size());
    Stream* s = new Stream(datagram);

    emit UDPReceived(s);
}

void NetworkClient::onTCPReceive()
{
    QByteArray data = tcpSocket_->readAll();
    Stream* s = new Stream(data);

    emit TCPReceived(s);
}

} /* End of namespace */
