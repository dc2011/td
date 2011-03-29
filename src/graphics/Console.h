#ifndef _console_
#define _console_

#include <QObject>
#include <QMutex>
#include <QVector>
#include <QString>
#include <QGraphicsTextItem>
#include "../util/mutex_magic.h"

namespace td {

class Console : public QObject {
    Q_OBJECT

    THREAD_SAFE_SINGLETON

private:
    
    static Console* instance_;
    static QVector<QString> *display_;
    static QGraphicsTextItem *label_;

    explicit Console();
    ~Console();

public:

    static Console* instance() {
        mutex_.lock();
        if (instance_ == NULL) {
            instance_ = new Console();
        }
        mutex_.unlock();	
        return instance_;
    }
    
    void addText(QString text);

};

}

#endif
