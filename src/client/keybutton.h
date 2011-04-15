#ifndef KEYBUTTON_H
#define KEYBUTTON_H

#include <QPushButton>
#include <QKeyEvent>

namespace td {

class KeyButton : public QPushButton
{
    Q_OBJECT

protected:
    /** The key sequence that is assigned. */
    QKeySequence keyseq_;

    /** The previous key sequence that was assigned. */
    QKeySequence oldseq_;

public:
    explicit KeyButton(QWidget* parent = 0);
    virtual ~KeyButton();

protected:
    virtual bool event(QEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

    void updateShortcutDisplay();

signals:
    void setSequence(QKeySequence seq);
};

} /* end namespace td */

#endif
