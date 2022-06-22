#include "mainwindow.h"
#include "datamanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    DataManager dataManager = DataManager(nullptr);
    QApplication a = QApplication(argc, argv);
    MainWindow w = MainWindow();
    w.show();
    return a.exec();
}
