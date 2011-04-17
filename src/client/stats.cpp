#include "stats.h"
#include "ui_stats.h"

Stats::Stats(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Stats)
{
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
    ui->hp_label->setText(QString::number(value));
}
void Stats::updateGems(int value){
    ui->hp_label->setText(QString::number(value));
}


/**
 * Update
 *
 * int x = ui->name->text.toInt();
 * x++;
 * ui->name->setText(QString::number(x));
 */
