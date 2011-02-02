#include "netclient.h"
#include <ctime>


namespace td {

NetworkClient* NetworkClient::instance_ = NULL;
QMutex NetworkClient::mutex_;
QQueue<QByteArray> NetworkClient::msgQueue_;
QTcpSocket* NetworkClient::tcpSocket_;
QUdpSocket* NetworkClient::udpSocket_;
QHostAddress NetworkClient::serverAddr_;


NetworkClient::NetworkClient()
{
    //Doesn't work....
    /* QFuture<void> future =
    QtConcurrent::run(this, &NetworkClient::sendQueue);*/
}

NetworkClient::~NetworkClient()
{
    /*clean up here*/
    msgQueue_.dequeue(); //placeholder
}


void NetworkClient::setServerAddr(QHostAddress servAddr)
{
    mutex_.lock();
    serverAddr_ = servAddr;
    mutex_.unlock();
}

void NetworkClient::sendQueue()
{
    QByteArray tmp;
    QUdpSocket* udpSocket = new QUdpSocket(this);

    while (1) {
        if (msgQueue_.size() > 0) {

            mutex_.lock();
            tmp = msgQueue_.dequeue();
            mutex_.unlock();
           
            udpSocket->writeDatagram(tmp, tmp.size(),
                                     QHostAddress::Broadcast, 26691);
        } else {
	     //TODO: Fix this sleep 
            sleep(1);
        }
    }
}

} /* End of namespace */
