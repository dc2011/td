#ifndef KEYMAP_H
#define KEYMAP_H

#include <QDialog>
#include <QKeySequence>

namespace Ui {
    class Keymap;
}

namespace td {

class Keymap : public QDialog
{
    Q_OBJECT

public:
    explicit Keymap(QWidget *parent = 0);
    ~Keymap();

private slots:
    void closewindow();

private:
    Ui::Keymap *ui;

    QKeySequence menuKey;
};

} /* end namespace td */

#endif // KEYMAP_H
