#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>

namespace Ui {
    class MainMenu;
}
namespace td {

class MainMenu : public QDialog
{
    Q_OBJECT
private:
    /** the form object used to access its user interface */
    Ui::MainMenu *ui;
    /** The current display state of this window. */
    bool showing_;

    QPoint clickPos;

public:
    /**
     * Constructs the mainmenu and sets and the signals and slots bewtween the
     * different forms.
     *
     * @author Warren Voelkl
     */
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

protected:
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);

private slots:
    /**
     * Handls the Ok button press. Calls show main menu.
     * @author Warren Voelkl
     */
    void slotPushOk();
    /**
     * Handles the volume button.
     * Makes the push button window visible and hides this one
     * @author Warren Voelkl
     */
    void slotPushSettings();
    /**
     * gets the qApplication and calls quit on the program.
     * @author Warren Voelkl
     */
    void slotPushQuit();

    /**
     * calls the keymapping window and on ok it sets the selected values
     * on cancel it just unhides this window and effects nothing.
     * @author Warren Voelkl, Darryl Pogue
     */
    void slotPushKey();
public slots:
    /**
     * Used to hide/show this window
     * @author Warren Voelkl
     */
    void slotShowMainMenu();
signals:
    /**
     * Tells the volume window when to display.
     * @author Warren Voelkl
     */
    void signalVolumeWindow();
};

}

#endif // MAINMENU_H
