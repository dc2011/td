#include <QSettings>
#include "keymap.h"
#include "ui_keymap.h"
#include <QFile>

namespace td {

KeymapDialog::KeymapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeymapDialog)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->move(300, 200);

    QFile f(QString(":/file/client.qss"));
    f.open(QIODevice::ReadOnly);
    this->setStyleSheet(QString(f.readAll()));
    f.close();

    ui->setupUi(this);

    QSettings settings;
    settings.beginGroup("keymap");

    keys.choice1Key = QKeySequence(settings.value("choice1", "1").toString());
    ui->btnChoice1->setText(keys.choice1Key.toString());
    connect(ui->btnChoice1, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setChoice1(QKeySequence)));

    keys.choice2Key = QKeySequence(settings.value("choice2", "2").toString());
    ui->btnChoice2->setText(keys.choice2Key.toString());
    connect(ui->btnChoice2, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setChoice2(QKeySequence)));

    keys.choice3Key = QKeySequence(settings.value("choice3", "3").toString());
    ui->btnChoice3->setText(keys.choice3Key.toString());
    connect(ui->btnChoice3, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setChoice3(QKeySequence)));

    keys.choice4Key = QKeySequence(settings.value("choice4", "4").toString());
    ui->btnChoice4->setText(keys.choice4Key.toString());
    connect(ui->btnChoice4, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setChoice4(QKeySequence)));

    keys.choice5Key = QKeySequence(settings.value("choice5", "5").toString());
    ui->btnChoice5->setText(keys.choice5Key.toString());
    connect(ui->btnChoice5, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setChoice5(QKeySequence)));

    keys.choice6Key = QKeySequence(settings.value("choice6", "6").toString());
    /*ui->btnChoice6->setText(keys.choice6Key.toString());
    connect(ui->btnChoice6, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setChoice6(QKeySequence)));*/

    keys.choice7Key = QKeySequence(settings.value("choice7", "7").toString());
    /*ui->btnChoice7->setText(keys.choice7Key.toString());
    connect(ui->btnChoice7, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setChoice7(QKeySequence)));*/

    keys.choice8Key = QKeySequence(settings.value("choice8", "8").toString());
    /*ui->btnChoice8->setText(keys.choice8Key.toString());
    connect(ui->btnChoice8, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setChoice8(QKeySequence)));*/

    keys.choice9Key = QKeySequence(settings.value("choice9", "9").toString());
    /*ui->btnChoice9->setText(keys.choice9Key.toString());
    connect(ui->btnChoice9, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setChoice9(QKeySequence)));*/

    keys.menuKey = QKeySequence(settings.value("menu", "space").toString());
    ui->btnMenu->setText(keys.menuKey.toString());
    connect(ui->btnMenu, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setMenu(QKeySequence)));

    keys.extraInfoKey = QKeySequence(settings.value("extrainfo", "r").toString());
    ui->btnExtraInfo->setText(keys.extraInfoKey.toString());
    connect(ui->btnExtraInfo, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setExtraInfo(QKeySequence)));

    keys.voiceKey = QKeySequence(settings.value("voice", "v").toString());
    ui->btnVoice->setText(keys.voiceKey.toString());
    connect(ui->btnVoice, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setVoice(QKeySequence)));

    keys.zoomKey = QKeySequence(settings.value("zoom", "z").toString());
    ui->btnZoom->setText(keys.zoomKey.toString());
    connect(ui->btnZoom, SIGNAL(setSequence(QKeySequence)),
            this, SLOT(setZoom(QKeySequence)));

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

    settings.setValue("choice1", keys.choice1Key.toString());
    settings.setValue("choice2", keys.choice2Key.toString());
    settings.setValue("choice3", keys.choice3Key.toString());
    settings.setValue("choice4", keys.choice4Key.toString());
    settings.setValue("choice5", keys.choice5Key.toString());
    settings.setValue("choice6", keys.choice6Key.toString());
    settings.setValue("choice7", keys.choice7Key.toString());
    settings.setValue("choice8", keys.choice8Key.toString());
    settings.setValue("choice9", keys.choice9Key.toString());

    settings.setValue("menu", keys.menuKey.toString());
    settings.setValue("extrainfo", keys.extraInfoKey.toString());
    //settings.setValue("console", keys.consoleKey.toString());
    settings.setValue("voice", keys.voiceKey.toString());
    settings.setValue("zoom", keys.zoomKey.toString());

    settings.setValue("arrowup", keys.arrowUp.toString());
    settings.setValue("arrowdown", keys.arrowDown.toString());
    settings.setValue("arrowleft", keys.arrowLeft.toString());
    settings.setValue("arrowright", keys.arrowRight.toString());

    settings.endGroup();

    QDialog::accept();
}

void KeymapDialog::setChoice1(QKeySequence seq) {
    keys.choice1Key = seq;
}

void KeymapDialog::setChoice2(QKeySequence seq) {
    keys.choice2Key = seq;
}

void KeymapDialog::setChoice3(QKeySequence seq) {
    keys.choice3Key = seq;
}

void KeymapDialog::setChoice4(QKeySequence seq) {
    keys.choice4Key = seq;
}

void KeymapDialog::setChoice5(QKeySequence seq) {
    keys.choice5Key = seq;
}

void KeymapDialog::setChoice6(QKeySequence seq) {
    keys.choice6Key = seq;
}

void KeymapDialog::setChoice7(QKeySequence seq) {
    keys.choice7Key = seq;
}

void KeymapDialog::setChoice8(QKeySequence seq) {
    keys.choice8Key = seq;
}

void KeymapDialog::setChoice9(QKeySequence seq) {
    keys.choice9Key = seq;
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

void KeymapDialog::setZoom(QKeySequence seq) {
    keys.zoomKey = seq;
}

} /* end namespace td */
