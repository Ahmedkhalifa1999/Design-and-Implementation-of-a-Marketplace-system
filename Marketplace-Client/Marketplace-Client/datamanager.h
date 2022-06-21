#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QString>
#include <mainwindow.h>

typedef struct {
    const QString &firstName;
    const QString &lastName;
    const QString &email;
    const QString &password;
    const QString &address;
    const QString &phone;
} SignUpData;

typedef struct {
    const QString &email;
    const QString &password;
} SignInData;

typedef struct {
    unsigned int ID;
    unsigned int quantity;
} CartItem;

typedef struct {
    QString &name;
    QPixmap &icon;
    unsigned int quantity;
} DetailedCartItem;

typedef struct {
    unsigned int ID;
    bool availableQuantity;
} CheckoutResult;

class DataManager : public QObject
{
    Q_OBJECT


public:
    explicit DataManager(QObject *parent = nullptr);

    //Sign-in & sign-up methods
    bool signUp(SignUpData data, MainWindow &caller, bool &validEmail, bool &validPhone);
    bool signIn(SignInData data, MainWindow &caller);
    bool autoSignIn(QString &email, MainWindow &caller);

    //Cart-related functionality
    std::vector<DetailedCartItem> &viewCart();
    void addToCart(CartItem item);
    void updateCart(std::vector<CartItem> &updated);
    void checkout(MainWindow &caller);

    //Account-related functionality
    void getAccountDetails();
    void getOrderHistory();
    void walletDeposit();

    //Shop-related functionality
    void getItemList();
    void getItemData();

public slots:

signals:
    //Sign-in & sign-up signals
    void signUp_signal(bool result);
    void signIn_signal(bool result);

    //Cart-related signals
    void checkout_signal(bool result, std::vector<CheckoutResult> detailedResult);
};

#endif // DATAMANAGER_H
