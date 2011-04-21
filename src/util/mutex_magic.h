#ifndef _mutex_magic_
#define _mutex_magic_

#include <QMutex>

#define THREAD_SAFE_CLASS \
protected: \
    /** 
     A Mutex to protect data from multiple threads. 
      
     This must be used any time instance data is read or updated.
     */ \
    QMutex mutex_;

#define THREAD_SAFE_SINGLETON \
private: \
    /** 
     A Mutex to protect instance data from multiple threads. 
      
     This must be used any time instance data is read or updated, 
     as well as when the singleton object is checked and initialized. 
     This is static because it needs to be used in the instance() method. 
     */ \
    static QMutex mutex_;

#define SAFE_OPERATION(x) \
    mutex_.lock(); \
    x; \
    mutex_.unlock();

#endif
