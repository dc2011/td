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
QGraphicsView* Console::view_;
int Console::y=-150;
QTextCharFormat charFormat;

Console::Console() {

    display_ = new QVector<QString>();
    label_ = new QGraphicsTextItem();
    textLabel_ = new QGraphicsTextItem();
    rect_ = new QGraphicsRectItem();
    textRect_ = new QGraphicsRectItem();
    view_ = CDriver::instance()->getMainWindow()->getView();

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
    display_->push_front(text.leftJustified(49));

    for(int i=0; i < display_->size(); i++) {
        tmp.append(display_->at(i));
        tmp.append("\n");
    }
    
    QTextCursor cursor = QTextCursor(doc);
    cursor.insertText(tmp, charFormat);

    label_->setDocument(doc);
    
    translate();
    mutex_.unlock();
}

void Console::hide() {
    y=-150;
    label_->hide();
    rect_->hide();

    translate();
    text_ = "Say: ";
    textLabel_->hide();
    textRect_->hide();
}

void Console::show() {
    connect(CDriver::instance()->getTimer(), SIGNAL(timeout()), 
            this, SLOT(scroll()));
    
    translate();

    label_->show();
    rect_->show();
    textLabel_->show();
    textRect_->show();
}

void Console::scroll() {
    
    translate();

    if(y>=30) {
        y=30;
        disconnect(CDriver::instance()->getTimer(), SIGNAL(timeout()), 
            this, SLOT(scroll()));
	return;
    }
    y+=10;
}

void Console::toggle() {
    if(label_->isVisible()) {
        hide();
    } else {
        show();
    }
}

void Console::translate() {
    
    QRect a = label_->boundingRect().toRect();
    QRect b = textLabel_->boundingRect().toRect();
    int xSize, xDiff = 0;
    
    if(a.topRight().x() > b.topRight().x()) {
	xSize = a.topRight().x();
    } else {
	xSize = b.topRight().x();
	xDiff = b.topRight().x() - a.topRight().x();
    }

    QPointF aPoint = view_->mapToScene(0,0);
    textLabel_->setPos(aPoint);
    textRect_->setRect(aPoint.x(),aPoint.y(),xSize,30);
    
    aPoint = view_->mapToScene(0,y);
    label_->setPos(aPoint);

    QRectF rRect = label_->boundingRect().adjusted(0,y,0,y);
    rRect.setRight(rRect.right() + xDiff);
    QPolygonF rPoly = view_->mapToScene(rRect.toRect());
    rect_->setRect(rPoly.boundingRect());

    label_->update();
    rect_->update();
    textLabel_->update();
    textRect_->update();

}

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
    translate();
}

}; //end of namespace
