#include <QSettings>
#include "keymap.h"
#include "ui_keymap.h"

namespace td {

KeymapDialog::KeymapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeymapDialog)
{
    ui->setupUi(this);

    QSettings settings;
    settings.beginGroup("keymap");

    keys.menuKey = QKeySequence(settings.value("menu", "space").toString());
    ui->btnMenu->setText(keys.menuKey.toString());

    keys.extraInfoKey = QKeySequence(settings.value("extrainfo", "r").toString());
    ui->btnExtraInfo->setText(keys.extraInfoKey.toString());

    keys.consoleKey = QKeySequence(settings.value("console", "`").toString());
    ui->btnConsole->setText(keys.consoleKey.toString());

    keys.voiceKey = QKeySequence(settings.value("voice", "v").toString());
    ui->btnVoice->setText(keys.voiceKey.toString());

    keys.arrowUp = QKeySequence(settings.value("arrowup", "up").toString());
    ui->btnArrowUp->setText(keys.arrowUp.toString());

    keys.arrowDown = QKeySequence(settings.value("arrowdown", "down").toString());
    ui->btnArrowDown->setText(keys.arrowDown.toString());

    keys.arrowLeft = QKeySequence(settings.value("arrowleft", "left").toString());
    ui->btnArrowLeft->setText(keys.arrowLeft.toString());

    keys.arrowRight = QKeySequence(settings.value("arrowright", "right").toString());
    ui->btnArrowRight->setText(keys.arrowRight.toString());

    settings.endGroup();

    connect(this, SIGNAL(accepted()), this, SLOT(closewindow()));
}

KeymapDialog::~KeymapDialog()
{
    delete ui;
}

void KeymapDialog::closewindow() {
    QSettings settings;
    settings.beginGroup("keymap");

    settings.setValue("menu", keys.menuKey.toString());
    settings.setValue("extrainfo", keys.extraInfoKey.toString());
    settings.setValue("console", keys.consoleKey.toString());
    settings.setValue("voice", keys.voiceKey.toString());

    settings.endGroup();
}

} /* end namespace td */
