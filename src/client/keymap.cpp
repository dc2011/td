#include "keymap.h"
#include "ui_keymap.h"

namespace td {

Keymap::Keymap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Keymap)
{
    ui->setupUi(this);
}

Keymap::~Keymap()
{
    delete ui;
}

} /* end namespace td */
