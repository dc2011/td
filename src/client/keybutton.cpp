#include "keybutton.h"

namespace td {

KeyButton::KeyButton(QWidget* parent) : QPushButton(parent) {
    this->setCheckable(true);
}

KeyButton::~KeyButton() { }

/* prevent Qt from special casing Tab and Backtab */
bool KeyButton::event(QEvent* e) {
   if (this->isChecked() && e->type() == QEvent::KeyPress) {
       keyPressEvent(static_cast<QKeyEvent*>(e));
       return true;
   }

   /* The shortcut 'alt+c' (or any other dialog local action shortcut)
    ended the recording and triggered the action associated with the
    action. In case of 'alt+c' ending the dialog.  It seems that those
    ShortcutOverride events get sent even if grabKeyboard() is active. */
   if (this->isChecked() && e->type() == QEvent::ShortcutOverride) {
       e->accept();
       return true;
   }

   return QPushButton::event(e);
}

void KeyButton::keyPressEvent(QKeyEvent* e) {
    int keyQt = e->key();
    if (keyQt == -1) {
        /* Qt sometimes returns garbage keycodes, I observed -1, if it
         doesn't know a key. We cannot do anything useful with those
         (several keys have -1, indistinguishable) and QKeySequence.
         toString() will also yield a garbage string. */
        return;
    }

    if (!this->isChecked()) {
        return QPushButton::keyPressEvent(e);
    }

    oldseq_ = keyseq_;

    e->accept();

    switch(keyQt) {
        case Qt::Key_AltGr:
        case Qt::Key_Alt:
        case Qt::Key_Shift:
        case Qt::Key_Meta:
        case Qt::Key_Control:
        case Qt::Key_Menu:
            return;
        default:
        {
            if (keyQt) {
                keyseq_ = QKeySequence(keyQt);
                this->setChecked(false);
                this->clearFocus();
                emit setSequence(keyseq_);
            }

            updateShortcutDisplay();
        }
    }
}

void KeyButton::keyReleaseEvent(QKeyEvent* e) {
    if (e->key() == -1) {
        /* ignore garbage, see keyPressEvent() */
        return;
    }

    if (!this->isChecked()) {
        return QPushButton::keyReleaseEvent(e);
    }

    e->accept();
}

void KeyButton::updateShortcutDisplay() {
    /* empty string if no non-modifier was pressed */
    QString s = keyseq_.toString();

    s.prepend(' ');
    s.append(' ');
    this->setText(s);
}

} /* end namespace td */
