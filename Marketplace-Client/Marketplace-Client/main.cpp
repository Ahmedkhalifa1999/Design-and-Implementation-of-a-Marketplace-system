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
    MainWindow window = MainWindow();

    //Connect data manager signals to main window slots
    //Sign-in & sign-up connections
    QObject::connect(&dataManager, &DataManager::signUp_signal, &window, &MainWindow::signUp_slot);
    QObject::connect(&dataManager, &DataManager::signIn_signal, &window, &MainWindow::signIn_slot);
    //Cart-related connections
    QObject::connect(&dataManager, &DataManager::checkout_signal, &window, &MainWindow::checkout_slot);
    //Account-related connections
    QObject::connect(&dataManager, &DataManager::getAccountDetails_signal, &window, &MainWindow::getAccountDetails_slot);
    QObject::connect(&dataManager, &DataManager::updateAccountDetails_signal, &window, &MainWindow::updateAccountDetails_slot);
    QObject::connect(&dataManager, &DataManager::getOrderHistory_signal, &window, &MainWindow::getOrderHistory_slot);
    QObject::connect(&dataManager, &DataManager::getOrderDetails_signal, &window, &MainWindow::getOrderDetails_slot);
    QObject::connect(&dataManager, &DataManager::walletDeposit_signal, &window, &MainWindow::walletDeposit_slot);
    //Shop-related connections
    QObject::connect(&dataManager, &DataManager::getItemList_signal, &window, &MainWindow::getItemList_slot);
    QObject::connect(&dataManager, &DataManager::getItemData_signal, &window, &MainWindow::getItemData_slot);
    QObject::connect(&dataManager, &DataManager::getCategories_signal, &window, &MainWindow::getCategories_slot);

    window.show();
    return application.exec();
}
