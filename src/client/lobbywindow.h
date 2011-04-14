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
    void onCreateNewGame();

private slots:
    /**
     * Records the last used settings in a persistent file.
     *
     * @author Dean Morin
     */
    void writeSettings();

    /** Sends a chat message
     *
     * @author Kelvin Lui
     * @param nickName the nickName of the sender
     * @param chatMessage the messgae to send
     **/
    void sendChatMessage();


private:
    void updateListOfUserNames(QList<QString*>&);
    void updateListOfGames(QMultiMap<int,QString>&);
    /**
     * Reads the last used settings from a persistent file.
     *
     * @author Dean Morin
     */
    void readSettings();

    

    /**
     *
     *@author Kelvin Lui
     *@param msg The new chat message to display
     */
    void displayChatMsgRx(QString& nickName, QString& msg);

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
