#include "lobbywindow.h"
#include <QDateTime>
#include <QMessageBox>
#include <QSettings>
#include <QFile>
#include "../audio/SfxManager.h"
#include "../engine/CDriver.h"
#include "../network/netclient.h"
#include "../../uic/ui_lobbywindow.h"

namespace td {

LobbyWindow::LobbyWindow(QWidget *parent) :
    QMainWindow(parent),
    gameNum_(0),
    ui(new Ui::LobbyWindow)

{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->move(40, 40);

    ui->setupUi(this);
    setCursor(QCursor(QPixmap(":/file/cursor.png")));
    ui->btnStart->setEnabled(false);
    ui->userList->header()->setResizeMode(QHeaderView::Fixed);

    this->applyStyleSheet(QString(":/file/client.qss"));


    connect(ui->btnConnect, SIGNAL(clicked()),
            this, SLOT(connectLobby()));
    connect(ui->btnStart, SIGNAL(clicked()),
            this, SLOT(tmp_startGame()));
    connect(ui->chkSingleplayer, SIGNAL(clicked(bool)),
            ui->btnConnect, SLOT(setDisabled(bool)));
    connect(ui->chkSingleplayer, SIGNAL(clicked(bool)),
            ui->btnStart, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(startGame(bool)),
            this, SLOT(close()));
    connect(ui->sendMsg,SIGNAL(clicked()),this,SLOT(sendChatMessage()));

    // so I don't have to enter the ip address, like, every freaking time
    connect(ui->txtAddress, SIGNAL(editingFinished()),
            this, SLOT(writeSettings()));
    connect(ui->txtUsername, SIGNAL(editingFinished()),
            this, SLOT(writeSettings()));

    connect(ui->btnExit, SIGNAL(clicked()), this, SLOT(close()));

    QCoreApplication::setOrganizationName("dc2011");
    QCoreApplication::setApplicationName("td");
    readSettings();
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}

void LobbyWindow::connectLobby()
{
    ui->txtAddress->setDisabled(true);
    ui->txtUsername->setDisabled(true);
    ui->btnConnect->setDisabled(true);
    ui->chkSingleplayer->setDisabled(true);

    QString ip = ui->txtAddress->text();
    QHostAddress addr(ip);

    NetworkClient::init(addr);
    connect(NetworkClient::instance(), SIGNAL(TCPReceived(Stream*)),
            this, SLOT(onTCPReceived(Stream*)));

    Stream* s = new Stream();
    s->writeShort(TD_VERSION);
    
    if (ui->txtUsername->text() == "username") {
        assignName();
    }
    s->writeByte(ui->txtUsername->text().length());
    s->write(ui->txtUsername->text().toAscii());

    PLAY_LOCAL_SFX(SfxManager::lobbyConnect);
    NetworkClient::instance()->send(network::kLobbyWelcome, s->data());
    connect(ui->newGame,SIGNAL(clicked()),this,SLOT(onCreateNewGame()));
    connect(ui->leaveGame,SIGNAL(clicked()),this,SLOT(onLeaveGame()));
    connect(ui->gameList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onJoinGame(QListWidgetItem*)));

    delete s;
}

void LobbyWindow::tmp_startGame()
{
    PLAY_LOCAL_SFX(SfxManager::lobbyStart);
//    alSleep(2); //needs fixing
    if (ui->chkSingleplayer->isChecked()) {
        emit startGame(true);
        return;
    }

    Stream s;
    s.writeInt(gameNum_);
    NetworkClient::instance()->send(network::kLobbyStartGame, s.data());
}

void LobbyWindow::onTCPReceived(Stream* s)
{
    unsigned char msgType = s->readByte();

    switch (msgType) {
        case network::kLobbyWelcome:
        {
            int players = s->readInt();
            ui->lblDisplayCount->setText(QString::number(players));

            if (players == 1) {
                ui->btnStart->setEnabled(true);
            }
            
            break;
        }
        case network::kChatMessage:
        {
            int nameLen = s->readInt();
            QString nickName(s->read(nameLen));
            int msgLen = s->readInt();
            QString msg(s->read(msgLen));
            displayChatMsgRx(nickName,msg);
            break;
        }

        case network::kUpdateUserList:
        {
            QMultiMap<int,QString> userList;
            int numOfPlayers = s->readInt();
            for(int i = 0; i < numOfPlayers; i++) {
                int nameLen = s->readInt();
                QString name(s->read(nameLen));
                int game = s->readInt();
                userList.insert(game,name);

            }
            updateListOfUserNames(userList);
            break;
        }
        case network::kUpdateListOfGames:
        {
            QMultiMap<int,QString> gameList;
            int numOfGames = s->readInt();
            for(int i = 0; i < numOfGames; i++) {
                int gameName = s->readInt();
                int numOfPlayers = s->readInt();
                for(int j = 0; j < numOfPlayers; j++) {
                    int nameLen = s->readInt();
                    gameList.insert(gameName,(s->read(nameLen)));   
                    
                }
                   
            }
            updateListOfGames(gameList);
            break;
        }
        case network::kGameId:
        {
            gameNum_ = s->readInt();
            break;
        }
        case network::kLobbyStartGame:
        {
            connect(NetworkClient::instance(), SIGNAL(UDPReceived(Stream*)),
                    CDriver::instance(), SLOT(UDPReceived(Stream*)));
            connect(NetworkClient::instance(), SIGNAL(TCPReceived(Stream*)),
                    CDriver::instance(), SLOT(UDPReceived(Stream*)));
            disconnect(NetworkClient::instance(), SIGNAL(TCPReceived(Stream*)),
                    this, SLOT(onTCPReceived(Stream*)));
            emit startGame(false);
            break;
        }
        case network::kBadVersion:
        {
            QMessageBox(QMessageBox::Critical, "Tower Defense: Error",
                    "Your game version does not match the server.").exec();
            break;
        }
    }
    if(!s->eof()) {
        this->onTCPReceived(s);
    }
    else {
        delete s;
    }
}

void LobbyWindow::writeSettings() {
    QSettings settings;

    settings.setValue("address", ui->txtAddress->text());
    settings.setValue("username", ui->txtUsername->text());
}

void LobbyWindow::readSettings() {
    QSettings settings;

    ui->txtAddress->setText(settings.value("address", "127.0.0.1").toString());
    ui->txtUsername->setText(settings.value("username", "username").toString());
}

void LobbyWindow::assignName() {
    QString names[] = { "Dorthy", "Rose", "Blanche", "Sophia" };
    uint seed = QDateTime::currentDateTime().toTime_t();
    qsrand(seed);
    int rand = qrand() % 4;

    ui->txtUsername->setText(names[rand]);
}

void LobbyWindow::applyStyleSheet(QString path) {
    QFile f(path);
    f.open(QIODevice::ReadOnly);
    this->setStyleSheet(QString(f.readAll()));
    f.close();
}

void LobbyWindow::sendChatMessage() {
    if(ui->msgBox->text().size() > 0)
    {
        Stream s;
        s.writeInt(ui->txtUsername->text().size());
        s.write(ui->txtUsername->text().toAscii());
        s.writeInt(ui->msgBox->text().size());
        s.write(ui->msgBox->text().toAscii());
        NetworkClient::instance()->send(network::kChatMessage, s.data());
        ui->msgBox->clear();
    }
}
void LobbyWindow::updateListOfUserNames(QMultiMap<int, QString>& userList) {

    ui->userList->clear();
    foreach(QString name, userList) {
        QStringList tmpList(name);
        tmpList.append(userList.key(name) == 0 ? "Not In Game" : QString::number(userList.key(name)));
        QTreeWidgetItem *tmpItem = new QTreeWidgetItem(ui->userList, tmpList);
        ui->userList->addTopLevelItem(tmpItem);
    }

}
void LobbyWindow::updateListOfGames(QMultiMap<int, QString>& gameList) {

    if(ui->gameList->count() > 0) {
        ui->gameList->clear();
    }
    foreach(int gameName, QSet<int>(gameList.keys().toSet())) {
        QListWidgetItem* item = new QListWidgetItem;
        QString name(QString("Game").append(QString::number(gameName)).append(
                     QString("\t")).append(QString::number(gameList.values(gameName).size()).append(QString("/256"))));

        gameList.values(gameName).size();

        item->setText(name);
        item->setData(Qt::UserRole,gameName);
        ui->gameList->addItem(item);

    }
}

void LobbyWindow::onJoinGame(QListWidgetItem* item) {
    if(gameNum_ == 0) {
        int gameNum = item->data(Qt::UserRole).toInt();
        gameNum_ = gameNum;
        Stream s;
        s.writeInt(ui->txtUsername->text().size());
        s.write(ui->txtUsername->text().toAscii());
        s.writeInt(gameNum);

        NetworkClient::instance()->send(network::kJoinGame, s.data());
    }
}

void LobbyWindow::onLeaveGame() {
    if(gameNum_ != 0) {
        Stream s;
        s.writeInt(ui->txtUsername->text().size());
        s.write(ui->txtUsername->text().toAscii());
        s.writeInt(gameNum_);
        gameNum_ = 0;
        NetworkClient::instance()->send(network::kLobbyleaveGame, s.data());
    }
}

void LobbyWindow::displayChatMsgRx(QString& nickName, QString& msg) {
    QString result(nickName);
    result.append(": ");
    result.append(msg);
    ui->msgView->append(result);
}

void LobbyWindow::onCreateNewGame() {
    if(gameNum_ == 0) {
        Stream s;
        s.writeInt(ui->txtUsername->text().size());
        s.write(ui->txtUsername->text().toAscii());
        s.writeInt(0);
        NetworkClient::instance()->send(network::kJoinGame, s.data());
    }
}
/* end namespace td */

};


