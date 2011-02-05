#include <QMainWindow>

#include "engine/ClientDriver.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //ClientDriver driver();
    //driver->Start();
    
    QMainWindow gui;
    gui.show();
    
    return a.exec();
}
