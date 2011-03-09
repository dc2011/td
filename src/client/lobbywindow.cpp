#include "lobbywindow.h"
#include "ui_lobbywindow.h"

LobbyWindow::LobbyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LobbyWindow)
{
    ui->setupUi(this);
}

LobbyWindow::~LobbyWindow()
{
    delete ui;
}
