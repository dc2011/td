#ifndef KEYMAP_H
#define KEYMAP_H

#include <QDialog>

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

private:
    Ui::Keymap *ui;
};

} /* end namespace td */

#endif // KEYMAP_H
