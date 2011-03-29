#include "Console.h"
#include "../engine/CDriver.h"
#include <QDebug>

namespace td {

Console* Console::instance_ = NULL;
QMutex Console::mutex_;
QVector<QString> *Console::display_;
QGraphicsTextItem *Console::label_; 

Console::Console() {

    display_ = new QVector<QString>();
    label_ = new QGraphicsTextItem();
    CDriver::instance()->getMainWindow()->getScene()->addItem(label_);
  
    label_->setDefaultTextColor (QColor(0,0,0));
    label_->setPos(15,15);
    label_->setVisible(false);
    label_->update();
}

Console::~Console() {}

void Console::addText(QString text) {
    
    QString tmp;

    mutex_.lock();
    if(display_->size() > 2) {
	display_->pop_back();
    }
    display_->push_front(text);

    for(int i=0; i < display_->size(); i++) {
	tmp.append(display_->at(i));
	tmp.append("\n");
    }
    
    qDebug() << tmp;
    label_->setPlainText(tmp);
    label_->update();
    
    mutex_.unlock();
}


} //end of namespace
