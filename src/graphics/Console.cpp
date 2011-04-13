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
QGraphicsRectItem *Console::rect_;
int Console::y=-115;

Console::Console() {

    display_ = new QVector<QString>();
    label_ = new QGraphicsTextItem();
    rect_ = new QGraphicsRectItem();
    CDriver::instance()->getMainWindow()->getScene()->addItem(label_);
    CDriver::instance()->getMainWindow()->getScene()->addItem(rect_);
    
    rect_->setRect(5,y-10,200,30);
    rect_->setBrush(QBrush(QColor(200,200,200)));
    rect_->setPen(QPen(QColor(200,200,200)));
    rect_->setZValue(98);
    rect_->setOpacity(0.35);
    
    label_->setDefaultTextColor(QColor(0,0,0));
    label_->setPos(15,y);
    label_->setTextWidth(240);
    label_->setZValue(99);
    label_->update();
    hide();
}

Console::~Console() {}

void Console::addText(QString text) {
    
    QString tmp;
    QTextDocument *doc = new QTextDocument();
    QTextCharFormat charFormat;
    QFont font("Monospace");
    font.setBold(true);
    QPen outlinePen = QPen (QColor(25, 200, 25), 0.2f, Qt::SolidLine);
    
    charFormat.setTextOutline(outlinePen);
    charFormat.setFont(font);
    charFormat.setFontPointSize(10);
    

    mutex_.lock();
    if(display_->size() > 4) {
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
    rect_->setRect(label_->boundingRect().adjusted(0,y,0,y));
    label_->update();
    rect_->update();
    
    mutex_.unlock();
}

void Console::hide() {
    y=-115;
    label_->hide();
    rect_->hide();
    label_->setPos(15,y);
    rect_->setRect(label_->boundingRect().adjusted(0,y,0,y));
    label_->update();
    rect_->update();    
}

void Console::show() {
    connect(CDriver::instance()->getTimer(), SIGNAL(timeout()), 
	    this, SLOT(scroll()));
    label_->show();
    rect_->show();
}

void Console::scroll() {
    y+=10;
    label_->setPos(15,y);
    rect_->setRect(label_->boundingRect().adjusted(0,y,0,y));
    if(y>=15) {
	y=15;
	disconnect(CDriver::instance()->getTimer(), SIGNAL(timeout()), 
	    this, SLOT(scroll()));
    }
    label_->update();
    rect_->update();
}

void Console::toggle() {
    if(label_->isVisible()) {
	hide();
    } else {
	show();
    }
};

} //end of namespace
