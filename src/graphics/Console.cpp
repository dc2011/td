#include "Console.h"
#include "../engine/CDriver.h"
#include <QDebug>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QGraphicsRectItem>

namespace td {

Console* Console::instance_ = NULL;
QMutex Console::mutex_;
QVector<QString> *Console::display_;
QGraphicsTextItem *Console::label_; 

Console::Console() {

    display_ = new QVector<QString>();
    label_ = new QGraphicsTextItem();
    QFont font("Monospace");
    QGraphicsRectItem *rect_ = new QGraphicsRectItem();
    CDriver::instance()->getMainWindow()->getScene()->addItem(label_);
    CDriver::instance()->getMainWindow()->getScene()->addItem(rect_);

    font.setPointSize(8);
    
    rect_->setRect(5,5,250,80);
    rect_->setBrush(QBrush(QColor(200,200,200)));
    rect_->setPen(QPen(QColor(200,200,200)));
    rect_->setZValue(98);
    rect_->setOpacity(0.35);
    
    label_->setFont(font);
    label_->setDefaultTextColor(QColor(0,0,0));
    label_->setPos(15,15);
    label_->setTextWidth(240);
    label_->setZValue(99);
    label_->update();
    

}

Console::~Console() {}

void Console::addText(QString text) {
    
    QString tmp;
    QTextDocument *doc = new QTextDocument();
    QTextCharFormat charFormat;
    QPen outlinePen = QPen (QColor(25, 200, 25), 0.2f, Qt::SolidLine);
    charFormat.setTextOutline(outlinePen);

    mutex_.lock();
    if(display_->size() > 2) {
	display_->pop_back();
    }
    display_->push_front(text.leftJustified(50));

    for(int i=0; i < display_->size(); i++) {
	tmp.append(display_->at(i));
	tmp.append("\n");
    }
    
    QTextCursor cursor = QTextCursor(doc);
    cursor.insertText(tmp, charFormat);

    label_->setDocument(doc);
    label_->update();
    
    mutex_.unlock();
}


} //end of namespace
