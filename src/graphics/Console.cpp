#include "Console.h"
#include "../engine/CDriver.h"

namespace td {

Console* Console::instance_ = NULL;
QMutex Console::mutex_;
QVector<QString> *Console::display_;
QGraphicsTextItem *Console::label_; 

Console::Console() {

    display_ = new QVector<QString>();
    label_ = new QGraphicsTextItem();
    CDriver::instance()->getMainWindow()->getScene()->addItem(label_);
    
    label_->setPlainText("Hello World");
    label_->setDefaultTextColor (QColor(0,0,0));
    label_->setPos(15,15);
    label_->setVisible(true);
    label_->update();
    qDebug("Created Label");
}

Console::~Console() {}

void Console::addText(QString text) {
    display_->push_front(text);
    label_->setPlainText(text);
    label_->update();
    qDebug("updated console");    
}


} //end of namespace
