#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

namespace Ui {
    class settingsWindow;
}

namespace td {

class settingsWindow : public QDialog
{
    Q_OBJECT
public:
    explicit settingsWindow(QWidget *parent = 0);
    ~settingsWindow();

private:
    Ui::settingsWindow* ui;
    int voiceLevel_;
    int sfxLevel_;
    int musicLevel_;
    bool isShowing_;
    void setVoice(int n);
    void setMusic(int n);
    void setSfx(int n);
public slots:
    void slotShowSettings();
private slots:
    void muteVoice(bool);
    void muteSfx(bool);
    void muteMusic(bool);
    void volumeVoice(int n);
    void volumeSfx(int n);
    void volumeMusic(int n);
signals:
    void setMusicSlider(int i);
    void setVoiceSlider(int i);
    void setSfxSlider(int i);
    void setMusicLabel(QString str);
    void setSfxLabel(QString str);
    void setVoiceLabel(QString str);
};

}

#endif // SETTINGSWINDOW_H
