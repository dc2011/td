#include <QSettings>
#include "keymap.h"
#include "ui_keymap.h"

namespace td {

Keymap::Keymap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Keymap)
{
    ui->setupUi(this);

    QSettings settings;
    settings.beginGroup("keymap");
    menuKey = QKeySequence(settings.value("menu", "Space").toString());
    settings.endGroup();

    connect(this, SIGNAL(close()), this, SLOT(closewindow()));
}

Keymap::~Keymap()
{
    delete ui;
}

void Keymap::closewindow() {
    QSettings settings;
    settings.beginGroup("keymap");

    settings.setValue("menu", menuKey.toString());

    settings.endGroup();
}

} /* end namespace td */
