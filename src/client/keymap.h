#ifndef KEYMAP_H
#define KEYMAP_H

#include <QDialog>
#include <QKeySequence>

namespace Ui {
    class KeymapDialog;
}

namespace td {

struct Keymap {
    QKeySequence choice1Key;
    QKeySequence choice2Key;
    QKeySequence choice3Key;
    QKeySequence choice4Key;
    QKeySequence choice5Key;
    QKeySequence choice6Key;
    QKeySequence choice7Key;
    QKeySequence choice8Key;
    QKeySequence choice9Key;

    QKeySequence menuKey;
    QKeySequence extraInfoKey;
    QKeySequence consoleKey;
    QKeySequence voiceKey;
    QKeySequence zoomKey;

    QKeySequence arrowUp;
    QKeySequence arrowDown;
    QKeySequence arrowLeft;
    QKeySequence arrowRight;
};

class KeymapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeymapDialog(QWidget *parent = 0);
    ~KeymapDialog();

    void savemap();

private slots:
    void setChoice1(QKeySequence seq);
    void setChoice2(QKeySequence seq);
    void setChoice3(QKeySequence seq);
    void setChoice4(QKeySequence seq);
    void setChoice5(QKeySequence seq);
    void setChoice6(QKeySequence seq);
    void setChoice7(QKeySequence seq);
    void setChoice8(QKeySequence seq);
    void setChoice9(QKeySequence seq);

    void setArrowUp(QKeySequence seq);
    void setArrowDown(QKeySequence seq);
    void setArrowLeft(QKeySequence seq);
    void setArrowRight(QKeySequence seq);

    void setMenu(QKeySequence seq);
    void setExtraInfo(QKeySequence seq);
    void setConsole(QKeySequence seq);
    void setVoice(QKeySequence seq);
    void setZoom(QKeySequence seq);

private:
    Ui::KeymapDialog *ui;
    Keymap keys;
};

} /* end namespace td */

#endif // KEYMAP_H
