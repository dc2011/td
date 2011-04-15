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

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();
private slots:
    void slotPushOk();
    void slotPushSettings();
    void slotPushQuit();
    void slotPushKey();
public slots:
    void slotShowMainMenu();
signals:
    void signalVolumeWindow();
    void signalKeymapWindow();
private:
    Ui::MainMenu *ui;
    bool showing_;
};

}

#endif // MAINMENU_H
