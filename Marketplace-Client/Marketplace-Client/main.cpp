#include "mainwindow.h"
#include "datamanager.h"

#include <QApplication>

#define SERVER_ADDRESS 0xc0a80164
#define SERVER_PORT 1500

int main(int argc, char *argv[])
{
    //Create required classes
    DataManager dataManager = DataManager(SERVER_ADDRESS, SERVER_PORT);
    QApplication application = QApplication(argc, argv);
    MainWindow window = MainWindow(&dataManager);

    window.show();
    return application.exec();
}
