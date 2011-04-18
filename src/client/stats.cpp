#include "stats.h"
#include "ui_stats.h"
#include <QFile>

Stats::Stats(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Stats)
{
    QFile f(QString(":/file/client.qss"));
    f.open(QIODevice::ReadOnly);
    this->setStyleSheet(QString(f.readAll()));
    f.close();

    ui->setupUi(this);
}

Stats::~Stats()
{
    delete ui;
}

void Stats::updateHP(int value){
    ui->hp_label->setText(QString::number(value));
}
void Stats::updateTime(int value){
    ui->time_label->setText(QString::number(value));
}
void Stats::updateGems(int value){
    ui->gem_label->setText(QString::number(value));
}


/**
 * Update
 *
 * int x = ui->name->text.toInt();
 * x++;
 * ui->name->setText(QString::number(x));
 */
