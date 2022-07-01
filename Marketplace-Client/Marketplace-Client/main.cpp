#include "mainwindow.h"
#include "datamanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Create required classes
    QTcpSocket *socket = new QTcpSocket();
    DataManager *dataManager = new DataManager(socket);
    QApplication application = QApplication(argc, argv);
    MainWindow window = MainWindow(dataManager);

    window.show();
    return application.exec();
}
