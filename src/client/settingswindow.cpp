#include "settingswindow.h"
#include "ui_settingswindow.h"

settingsWindow::settingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsWindow)
{
    ui->setupUi(this);
}

settingsWindow::~settingsWindow()
{
    delete ui;
}
