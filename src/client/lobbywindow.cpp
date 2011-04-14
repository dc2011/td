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
    ui(new Ui::LobbyWindow)
{
    ui->setupUi(this);
    ui->btnStart->setEnabled(false);

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
            QList<QString*> names;
            int numOfNames = s->readInt();
            for(int i = 0; i < numOfNames; i++) {
                int len = s->readInt();
                names.push_back(new QString(s->read(len)));
            }
            updateListOfUserNames(names);
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

    /*QStringList tmpList("Test Name");
    tmpList.append("Test Game");
    QTreeWidgetItem tmpItem(tmpList);

    ui->userList->addTopLevelItem(tmpItem);*/
}

void LobbyWindow::sendChatMessage() {
    Stream s;
    s.writeInt(ui->txtUsername->text().size());
    s.write(ui->txtUsername->text().toAscii());
    s.writeInt(ui->msgBox->text().size());
    s.write(ui->msgBox->text().toAscii());
    NetworkClient::instance()->send(network::kChatMessage, s.data());
    ui->msgBox->text().clear();
}
void LobbyWindow::updateListOfUserNames(QList<QString*>& userNames) {

}

void LobbyWindow::updateListOfGames(QMultiMap<int, QString>& gameList) {
    //update gui here
} 

void LobbyWindow::displayChatMsgRx(QString& nickName, QString& msg) {
    //update gui here
    //ui->msgView->text().append("hi");
    QString result(nickName);
    result.append(": ");
    result .append(msg);
    ui->msgView->setText(result);
}

void LobbyWindow::onCreateNewGame() {
    Stream s;
    s.writeInt(ui->txtUsername->text().size());
    s.write(ui->txtUsername->text().toAscii());
    s.writeInt(0);
    NetworkClient::instance()->send(network::kJoinGame, s.data());
}
/* end namespace td */

};


