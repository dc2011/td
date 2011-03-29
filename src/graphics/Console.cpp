#include "Console.h"
#include "../engine/CDriver.h"
#include <QDebug>
#include <QGraphicsRectItem>

namespace td {

Console* Console::instance_ = NULL;
QMutex Console::mutex_;
QVector<QString> *Console::display_;
QGraphicsTextItem *Console::label_; 

Console::Console() {

    display_ = new QVector<QString>();
    label_ = new QGraphicsTextItem();
    QGraphicsRectItem *rect_ = new QGraphicsRectItem();
    CDriver::instance()->getMainWindow()->getScene()->addItem(label_);
    CDriver::instance()->getMainWindow()->getScene()->addItem(rect_);

    rect_->setRect(5,5,200,80);
    rect_->setBrush(QBrush(QColor(200,200,200)));
    rect_->setPen(QPen(QColor(200,200,200)));
    rect_->setZValue(98);
    rect_->setOpacity(0.35);
    

    label_->setDefaultTextColor(QColor(50,50,50));
    label_->setPos(15,15);
    label_->setZValue(99);
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
    
    label_->setPlainText(tmp);
    label_->update();
    
    mutex_.unlock();
}


} //end of namespace
