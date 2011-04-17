#ifndef STATS_H
#define STATS_H

#include <QFrame>

namespace Ui {
    class Stats;
}

class Stats : public QFrame
{
    Q_OBJECT

public:
    explicit Stats(QWidget *parent = 0);
    ~Stats();

private:
    Ui::Stats *ui;

public slots:
    void updateHP(int value);
    void updateTime(int value);
    void updateGems(int value);
};

#endif // STATS_H
