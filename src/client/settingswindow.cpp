#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "../audio/manager.h"
#include <cstdio>
#include <QBitmap>
#include <QMouseEvent>
#include <QSettings>

namespace td {

settingsWindow::settingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsWindow)
{

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->move(400, 200);

    QPixmap pixmap("./img/mainMenuBg.png");
    this->setMask(pixmap.mask());

    QFile f(QString(":/file/client.qss"));
    f.open(QIODevice::ReadOnly);
    this->setStyleSheet(QString(f.readAll()));
    f.close();

    ui->setupUi(this);

    //from the ui to the files slots
    connect(ui->musicCheckBox, SIGNAL(toggled(bool)),this, SLOT(muteMusic(bool)));
    connect(ui->voiceCheckBox, SIGNAL(toggled(bool)), this, SLOT(muteVoice(bool)));
    connect(ui->sfxCheckBox, SIGNAL(toggled(bool)), this, SLOT(muteSfx(bool)));
    connect(ui->musicSlider, SIGNAL(valueChanged(int)), this, SLOT(volumeMusic(int)));
    connect(ui->voiceSlider, SIGNAL(valueChanged(int)), this, SLOT(volumeVoice(int)));
    connect(ui->sfxSlider, SIGNAL(valueChanged(int)), this, SLOT(volumeSfx(int)));

    //from this file to the ui's slots
    connect(this, SIGNAL(setMusicSlider(int)), ui->musicSlider,SLOT(setValue(int)));
    connect(this, SIGNAL(setVoiceSlider(int)), ui->voiceSlider,SLOT(setValue(int)));
    connect(this, SIGNAL(setSfxSlider(int)), ui->sfxSlider,SLOT(setValue(int)));

    connect(this, SIGNAL(setMusicLabel(QString)), ui->musicLabel,SLOT(setText(QString)));
    connect(this, SIGNAL(setVoiceLabel(QString)), ui->voiceLabel,SLOT(setText(QString)));
    connect(this, SIGNAL(setSfxLabel(QString)), ui->sfxLabel,SLOT(setText(QString)));
    connect(ui->pushButton, SIGNAL(released()),this,SLOT(slotShowSettings()));

    QSettings qs;
    qs.beginGroup("volume");

    setMusic(qs.value("music", 50).toInt());
    setVoice(qs.value("voice", 75).toInt());
    setSfx(qs.value("sfx", 50).toInt());
    qs.endGroup();
}

settingsWindow::~settingsWindow()
{
    delete ui;
}

void settingsWindow::muteMusic(bool toggled) {
    static int oldval = 0;
    if (toggled) {
        oldval = AudioManager::instance()->getMusicVol();
        emit setMusicSlider(0);
    } else {
        emit setMusicSlider(oldval);
    }
}


void settingsWindow::muteVoice(bool toggled) {
    static int oldval = 0;
    if (toggled) {
        oldval = AudioManager::instance()->getVoiceVol();
        emit setVoiceSlider(0);
    } else {
        emit setVoiceSlider(oldval);
    }
}

void settingsWindow::muteSfx(bool toggled) {
    static int oldval = 0;
    if (toggled) {
        oldval = AudioManager::instance()->getSfxVol();
        emit setSfxSlider(0);
    } else {
        emit setSfxSlider(oldval);
    }
}


void settingsWindow::setMusic(int n) {
    QString tmp;
    AudioManager::instance()->setMusicVol(n);
    emit setMusicLabel(tmp.setNum(n));
}

void settingsWindow::setVoice(int n) {
    QString tmp;
    AudioManager::instance()->setVoiceVol(n);
    emit setVoiceLabel(tmp.setNum(n));
}

void settingsWindow::setSfx(int n) {
    QString tmp;
    AudioManager::instance()->setSfxVol(n);
    emit setSfxLabel(tmp.setNum(n));
}

void settingsWindow::volumeVoice(int n) {
    voiceLevel_ = n;
    setVoice(n);
}

void settingsWindow::volumeSfx(int n) {
    sfxLevel_ = n;
    setSfx(n);
}

void settingsWindow::volumeMusic(int n) {
    musicLevel_ = n;
    setMusic(n);
}

void settingsWindow::slotShowSettings() {
    if (!isShowing_) {
        isShowing_ = true;
        voiceLevel_ = AudioManager::instance()->getVoiceVol();
        sfxLevel_ = AudioManager::instance()->getSfxVol();
        musicLevel_ = AudioManager::instance()->getMusicVol();
        emit setMusicSlider(musicLevel_);
        emit setVoiceSlider(voiceLevel_);
        emit setSfxSlider(sfxLevel_);
        this->show();
    } else {
        isShowing_ = false;
        this->hide();

        QSettings qs;
        qs.beginGroup("volume");
        qs.setValue("music", AudioManager::instance()->getMusicVol());
        qs.setValue("voice", AudioManager::instance()->getVoiceVol());
        qs.setValue("sfx", AudioManager::instance()->getSfxVol());
        qs.endGroup();

        emit signalWindowClosed();
    }
}

void settingsWindow::mousePressEvent( QMouseEvent *e ) {
    clickPos = e->pos();
}

void settingsWindow::mouseMoveEvent( QMouseEvent *e ) {
    move( e->globalPos() - clickPos );
}

}
