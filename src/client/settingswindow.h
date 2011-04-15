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
    /**
     * Constructor for this form makes the connections betweens the objects
     * corresponding form
     * @author Warren Voelkl
     */
    explicit settingsWindow(QWidget *parent = 0);
    ~settingsWindow();

private:
    /** The form object for connectin signals and slots */
    Ui::settingsWindow* ui;
    /** The current voice level */
    int voiceLevel_;
    /** the current SoundFx volume */
    int sfxLevel_;
    /** the current music volume */
    int musicLevel_;
    /** the showing state of this window */
    bool isShowing_;
    /**
     * used to set slider and label with the current volume settsings
     * @author Warren Voelkl
     */
    void setVoice(int n);
    /**
     * used to set slider and label with the current volume settsings
     * @author Warren Voelkl
     */
    void setMusic(int n);
    /**
     * used to set slider and label with the current volume settsings
     * @author Warren Voelkl
     */
    void setSfx(int n);
public slots:
    void slotShowSettings();
private slots:
    /**
     * Mutes the sound and saves the old value for unmuting
     * @author Warren Voelkl
     */
    void muteVoice(bool);
    /**
     * Mutes the sound and saves the old value for unmuting
     * @author Warren Voelkl
     */
    void muteSfx(bool);
    /**
     * Mutes the sound and saves the old value for unmuting
     * @author Warren Voelkl
     */
    void muteMusic(bool);
    /**
     * Sets the volume for this audio Type
     * @author Warren Voelkl
     */
    void volumeVoice(int n);
    /**
     * Sets the volume for this audio Type
     * @author Warren Voelkl
     */
    void volumeSfx(int n);
    /**
     * Sets the volume for this audio Type
     * @author Warren Voelkl
     */
    void volumeMusic(int n);
signals:
    void setMusicSlider(int i);
    void setVoiceSlider(int i);
    void setSfxSlider(int i);
    void setMusicLabel(QString str);
    void setSfxLabel(QString str);
    void setVoiceLabel(QString str);
    void signalWindowClosed();
};

}

#endif // SETTINGSWINDOW_H
