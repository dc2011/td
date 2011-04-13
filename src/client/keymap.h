#ifndef KEYMAP_H
#define KEYMAP_H

#include <QDialog>
#include <QKeySequence>

namespace Ui {
    class KeymapDialog;
}

namespace td {

struct Keymap {
    QKeySequence menuKey;
    QKeySequence extraInfoKey;
    QKeySequence consoleKey;
    QKeySequence voiceKey;

    QKeySequence arrowUp;
    QKeySequence arrowDown;
    QKeySequence arrowLeft;
    QKeySequence arrowRight;
};

class KeymapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeymapDialog(QWidget *parent = 0);
    ~KeymapDialog();

private slots:
    void closewindow();

private:
    Ui::KeymapDialog *ui;
    Keymap keys;
};

} /* end namespace td */

#endif // KEYMAP_H
