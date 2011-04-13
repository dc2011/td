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

    void applyStyleSheet(QString path);

signals:
    void startGame(bool singlePlayer);

public slots:
    void connectLobby();
    void tmp_startGame();
    void onTCPReceived(Stream* s);

private slots:
    /**
     * Records the last used settings in a persistent file.
     *
     * @author Dean Morin
     */
    void writeSettings();


private:
    void updateListOfUserNames(QList<QString*>);
    /**
     * Reads the last used settings from a persistent file.
     *
     * @author Dean Morin
     */
    void readSettings();

    /**
     * Assigns a username if the default is not changed.
     *
     * @author Dean Morin
     */
    void assignName();

    Ui::LobbyWindow *ui;
};

} /* end namespace td */

#endif // LOBBYWINDOW_H
