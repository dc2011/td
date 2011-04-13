#include "Console.h"
#include <QDebug>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QGraphicsRectItem>
#include "../engine/CDriver.h"
#include "../engine/Player.h"
#include "../network/netclient.h"

namespace td {

Console* Console::instance_ = NULL;
QMutex Console::mutex_;
QString Console::text_;
QVector<QString> *Console::display_;
QGraphicsTextItem *Console::label_; 
QGraphicsTextItem *Console::textLabel_; 
QGraphicsRectItem *Console::rect_;
QGraphicsRectItem *Console::textRect_;
int Console::y=-150;
QTextCharFormat charFormat;

//GLOBAL TODO HERE
/**
 * redraw whole area get rid of artifacting
 * clean up the formatting
 */

Console::Console() {

    display_ = new QVector<QString>();
    label_ = new QGraphicsTextItem();
    textLabel_ = new QGraphicsTextItem();
    rect_ = new QGraphicsRectItem();
    textRect_ = new QGraphicsRectItem();

    text_.append("Say: ");
    
    QFont font("Monospace");
    font.setBold(true);
    QPen outlinePen = QPen (QColor(25, 200, 25), 0.1f, Qt::SolidLine);
    
    charFormat.setTextOutline(outlinePen);
    charFormat.setFont(font);
    charFormat.setFontPointSize(10);

    QTextDocument *doc = new QTextDocument();
    QTextCursor cursor = QTextCursor(doc);
    cursor.insertText(text_, charFormat);
    textLabel_->setDocument(doc);
    textLabel_->update();
    
    
    CDriver::instance()->getMainWindow()->getScene()->addItem(label_);
    CDriver::instance()->getMainWindow()->getScene()->addItem(textLabel_);
    CDriver::instance()->getMainWindow()->getScene()->addItem(rect_);
    CDriver::instance()->getMainWindow()->getScene()->addItem(textRect_);
    
    rect_->setRect(0,y-10,400,30);
    rect_->setBrush(QBrush(QColor(200,200,200)));
    rect_->setPen(QPen(QColor(200,200,200)));
    rect_->setZValue(98);
    rect_->setOpacity(0.35);
    
    textRect_->setRect(0,0,400,30);
    textRect_->setBrush(QBrush(QColor(100,100,100)));
    textRect_->setPen(QPen(QColor(100,100,100)));
    textRect_->setZValue(98);
    textRect_->setOpacity(0.7);
    
    label_->setDefaultTextColor(QColor(0,0,0));
    label_->setPos(15,y);
    label_->setTextWidth(240);
    label_->setZValue(99);
    label_->update();
    
    textLabel_->setDefaultTextColor(QColor(0,0,0));
    textLabel_->setPos(3,3);
    textLabel_->setZValue(99);
    textLabel_->update();
    
    hide();
}

Console::~Console() {}

void Console::addText(QString text) {
    
    QString tmp;
    QTextDocument *doc = new QTextDocument();
    
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
    y=-150;
    label_->hide();
    rect_->hide();
    label_->setPos(15,y);
    rect_->setRect(label_->boundingRect().adjusted(0,y,0,y));
    label_->update();
    rect_->update();   
    text_ = "Say: ";
    textLabel_->hide();
    textRect_->hide();
}

void Console::show() {
    connect(CDriver::instance()->getTimer(), SIGNAL(timeout()), 
            this, SLOT(scroll()));
    label_->show();
    rect_->show();
    textLabel_->show();
    textRect_->show();
}

void Console::scroll() {
    y+=10;
    label_->setPos(15,y);
    rect_->setRect(label_->boundingRect().adjusted(0,y,0,y));
    if(y>=30) {
        y=30;
        disconnect(CDriver::instance()->getTimer(), SIGNAL(timeout()), 
            this, SLOT(scroll()));
    }
    label_->update();
    rect_->update();
    textLabel_->update();
    textRect_->update();
}

void Console::toggle() {
    if(label_->isVisible()) {
        hide();
    } else {
        show();
    }
}

//TODO clean up the same stuff from the 3 different functions
void Console::removeChar() {
    
    QString tmp;
    if(text_.length() <=5) {
        return;
    }
    text_.chop(1);
    
    QTextDocument *doc = new QTextDocument();
    
    QTextCursor cursor = QTextCursor(doc);
    tmp = text_;
    tmp.replace("\n","");
    cursor.insertText(tmp, charFormat);

    textLabel_->setDocument(doc);
    textLabel_->update();

}

void Console::addChar(QString c) {
    
    QString tmp;
    Stream s;

    text_.append(c);
    QTextDocument *doc = new QTextDocument();
    QTextCursor cursor = QTextCursor(doc);

    tmp = text_;
    tmp.replace("\n","");
    
    if(c.compare("\n") == 0) {

        if(CDriver::instance()->isSinglePlayer() == false) {
            s.writeInt(CDriver::instance()->getHuman()->getID());
            s.writeInt(tmp.length()-5);
            s.write(tmp.mid(5).toAscii());
            
            NetworkClient::instance()->send(network::kConsoleChat, s.data());
            
        }
        text_.clear();
        text_.append("Say: ");
        cursor.insertText(text_, charFormat);
    } else {
        cursor.insertText(tmp, charFormat);
    }

    textLabel_->setDocument(doc);
    textLabel_->update();
}

}; //end of namespace
