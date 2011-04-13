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
    
    /** The singleton instance */
    static Console* instance_;
    /** the text to be displayed */
    static QVector<QString> *display_;
    /** the label to display text */
    static QGraphicsTextItem *label_;
    /** the rect around the text */
    static QGraphicsRectItem *rect_;
    /** the rect around the text */
    static QGraphicsRectItem *textRect_;
    /** Y POS */
    static int y;
    /** Text chat */
    static QString text_;
    /** the label to display text */
    static QGraphicsTextItem *textLabel_;


    explicit Console();
    ~Console();

public:

    /**
     * Creates the instance of the Console
     * shamelessly stolen from dpogue
     *
     * @author Terence Stenvold
     */
    static Console* instance() {
        mutex_.lock();
        if (instance_ == NULL) {
            instance_ = new Console();
        }
        mutex_.unlock();	
        return instance_;
    }
    
    /**
     * Adds strings of a proper length
     * to the output console
     *
     * @author Terence Stenvold
     * @param text to add to the console
     */
    void addText(QString text);

    /**
     * hides the console 
     *
     * @author Terence Stenvold
     */
    void hide();
    
    /**
     * hides the console 
     *
     * @author Terence Stenvold
     */    
    void show();

    /**
     * toggles the console 
     *
     * @author Terence Stenvold
     */    
    void toggle();

    /**
     * An event filter
     *
     * @author Terence Stenvold
     * @param c is the char to add
     */
    void addChar(QString c);
    
    /**
     * removes a character for backspaces
     *
     * @author Terence Stenvold
     */
    void removeChar();

private slots:
    void scroll();

};

}

#endif
