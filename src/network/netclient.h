#ifndef _netclient_
#define _netclient_

#include <QMutex>
#include <QObject>
#include <QString>
#include <QThread>
#include <QtDebug>
#include <QByteArray>
#include <QtConcurrentRun>
#include <queue>


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
     
     static queue<QByteArray> msgQueue_; 
     
     explicit NetworkClient();
     ~NetworkClient();
     
    /**
     * Reads through the msgQueue_ and sends the data
     * either as UDP or TCP.
     *
     * This should be called in it's own thread.
     *
     * @author Terence Stenvold
     */ 
     void sendQueue();

    /**
     * Recieves data from the server and sends
     * a message to the driver to update??
     *
     * This should be called in it's own thread.
     *
     * @author Terence Stenvold
     */ 
     void recvData();

     
public:

    /**
     * Return the instance of the NetworkClient.
     * This creates a new instance the first time that it is called and 
     * always returns that instance when called further in the program's 
     * execution.
     *
     * @author Terence Stenvold
     * @return A pointer to the NetworkClient instance.
     */
     static NetworkClient* instance() {
	  mutex_.lock();
	  if (instance_ == NULL) {
	       instance_ = new AudioManager();
	  }
	  mutex_.unlock();
	  
	  return instance_;
     }

     /** 
      * Send the ByteArray to the server.
      *
      * This adds the msg to be sent to the server into
      * a queue meaning it will be sent as soon
      * as it can be but it doesn't block
      *
      * @author Terence Stenvold
      * @param msg as a byteArray 
      */
     void send(QByteArray msg) {
	  mutex_.lock();
	  msgQueue_.push(msg);
	  mutex_.unlock();
     }




     
     

}

} /*End of namespace*/


#endif
