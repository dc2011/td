#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QMainWindow>
#include <QNetworkAddressEntry>

namespace Ui {
    class LobbyWindow;
}

class LobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LobbyWindow(QWidget *parent = 0);
    ~LobbyWindow();

private:
    Ui::LobbyWindow *ui;
};

#endif // LOBBYWINDOW_H
