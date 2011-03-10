#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include "../util/defines.h"
#include "../network/stream.h"

namespace Ui {
    class LobbyWindow;
}

namespace td {

class LobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LobbyWindow(QWidget *parent = 0);
    ~LobbyWindow();

signals:
    void startGame(bool singlePlayer);

public slots:
    void connectLobby();
    void tmp_startGame();
    void onTCPReceived(Stream* s);

private:
    Ui::LobbyWindow *ui;
};

} /* end namespace td */

#endif // LOBBYWINDOW_H
