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

Console::Console() {

    display_ = new QVector<QString>();
    label_ = new QGraphicsTextItem();
    QFont font("Monospace");
    rect_ = new QGraphicsRectItem();
    CDriver::instance()->getMainWindow()->getScene()->addItem(label_);
    CDriver::instance()->getMainWindow()->getScene()->addItem(rect_);

    font.setPointSize(8);
    
    rect_->setRect(5,5,200,30);
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
    hide();
}

Console::~Console() {}

void Console::addText(QString text) {
    
    QString tmp;
    QTextDocument *doc = new QTextDocument();
    QTextCharFormat charFormat;
    QPen outlinePen = QPen (QColor(25, 200, 25), 0.2f, Qt::SolidLine);
    charFormat.setTextOutline(outlinePen);

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
    rect_->setRect(label_->boundingRect());
    label_->update();
    rect_->update();
    
    mutex_.unlock();
}

void Console::hide() {
    label_->hide();
    rect_->hide();
}

void Console::show() {
    label_->show();
    rect_->show();
}

void Console::toggle() {
    if(label_->isVisible()) {
	hide();
    } else {
	show();
    }
}

} //end of namespace
