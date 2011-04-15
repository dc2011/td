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
    connect(ui->btnMenu, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setMenu(QKeySequence)));

    keys.extraInfoKey = QKeySequence(settings.value("extrainfo", "r").toString());
    ui->btnExtraInfo->setText(keys.extraInfoKey.toString());

    keys.consoleKey = QKeySequence(settings.value("console", "`").toString());
    ui->btnConsole->setText(keys.consoleKey.toString());

    keys.voiceKey = QKeySequence(settings.value("voice", "v").toString());
    ui->btnVoice->setText(keys.voiceKey.toString());

    keys.arrowUp = QKeySequence(settings.value("arrowup", "up").toString());
    ui->btnArrowUp->setText(keys.arrowUp.toString());
    connect(ui->btnArrowUp, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setArrowUp(QKeySequence)));

    keys.arrowDown = QKeySequence(settings.value("arrowdown", "down").toString());
    ui->btnArrowDown->setText(keys.arrowDown.toString());
    connect(ui->btnArrowDown, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setArrowDown(QKeySequence)));

    keys.arrowLeft = QKeySequence(settings.value("arrowleft", "left").toString());
    ui->btnArrowLeft->setText(keys.arrowLeft.toString());
    connect(ui->btnArrowLeft, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setArrowLeft(QKeySequence)));

    keys.arrowRight = QKeySequence(settings.value("arrowright", "right").toString());
    ui->btnArrowRight->setText(keys.arrowRight.toString());
    connect(ui->btnArrowRight, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setArrowRight(QKeySequence)));

    settings.endGroup();
}

KeymapDialog::~KeymapDialog()
{
    delete ui;
}

void KeymapDialog::savemap() {
    QSettings settings;
    settings.beginGroup("keymap");

    settings.setValue("menu", keys.menuKey.toString());
    settings.setValue("extrainfo", keys.extraInfoKey.toString());
    settings.setValue("console", keys.consoleKey.toString());
    settings.setValue("voice", keys.voiceKey.toString());

    settings.setValue("arrowup", keys.arrowUp.toString());
    settings.setValue("arrowdown", keys.arrowDown.toString());
    settings.setValue("arrowleft", keys.arrowLeft.toString());
    settings.setValue("arrowright", keys.arrowRight.toString());

    settings.endGroup();

    QDialog::accept();
}

void KeymapDialog::setArrowUp(QKeySequence seq) {
    keys.arrowUp = seq;
}

void KeymapDialog::setArrowDown(QKeySequence seq) {
    keys.arrowDown = seq;
}

void KeymapDialog::setArrowLeft(QKeySequence seq) {
    keys.arrowLeft = seq;
}

void KeymapDialog::setArrowRight(QKeySequence seq) {
    keys.arrowRight = seq;
}

void KeymapDialog::setMenu(QKeySequence seq) {
    keys.menuKey = seq;
}

void KeymapDialog::setExtraInfo(QKeySequence seq) {
    keys.extraInfoKey = seq;
}

void KeymapDialog::setConsole(QKeySequence seq) {
    keys.consoleKey = seq;
}

void KeymapDialog::setVoice(QKeySequence seq) {
    keys.voiceKey = seq;
}

} /* end namespace td */
