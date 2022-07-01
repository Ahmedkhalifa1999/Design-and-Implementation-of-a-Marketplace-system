#include "mainwindow.h"
#include "datamanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Create required classes
    QApplication application = QApplication(argc, argv);
    QTcpSocket socket = QTcpSocket();
    DataManager dataManager = DataManager(&socket);
    MainWindow window = MainWindow(&dataManager);

    window.show();
    return application.exec();
}
