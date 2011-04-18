#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QListWidgetItem>
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
    void startGame(bool singlePlayer, QString map);

public slots:
    void connectLobby();
    void tmp_startGame();
    void onTCPReceived(Stream* s);
    void onCreateNewGame();

protected:
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    bool eventFilter(QObject *obj, QEvent *event);

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

    /** Called when a user double clicks on a game
     *
     * @author Kelvin Lui
     * @param  item the qlistwidgetItem that was clicked
     **/

    void onJoinGame(QListWidgetItem*);
    /**
      * Called when a user clicks on the leave game button
      * @author Kelvin Lui
      **/
    void onLeaveGame();

private:
    void updateListOfUserNames(QMultiMap<int, QString>&);
    void updateListOfGames(QMultiMap<int,QString>&);

    /**
     * Fills the list of maps from the list of map names.
     *
     * @author Darryl Pogue
     * @param mapList The list of map names.
     */
    void setListOfMaps(QStringList& mapList);

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

    /** List of all available maps. */
    QStringList maps_;

    /** the game number the client is connected to*/
    int gameNum_;
    Ui::LobbyWindow *ui;

    QPoint clickPos;
};

} /* end namespace td */

#endif // LOBBYWINDOW_H
