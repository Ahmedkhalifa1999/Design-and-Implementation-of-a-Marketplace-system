#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QTcpSocket>
#include "buttonid.h"

typedef struct {
    unsigned int pounds;
    unsigned int piasters;
} MoneyAmount;

typedef struct {
    QString firstName;
    QString lastName;
    QString email;
    QString password;
    QString address;
    QString phone;
} SignUpData;

typedef struct {
    bool validEmail;
    bool ValidPhone;
} SignUpResult;

typedef struct {
    QString email;
    QString password;
} SignInData;

typedef struct {
    bool result;
    QString email;
} AutoSignInResult;

typedef struct {
    unsigned int ID;
    unsigned int quantity;
} CartItem;

typedef struct {
    unsigned int ID;
    QString name;
    QPixmap icon();
    MoneyAmount price;
    unsigned int quantity;
} DetailedCartItem, DetailedOrderItem;

typedef struct {
    unsigned int ID;
    bool availableQuantity;
} CheckoutItem;

typedef struct {
    bool unavailableItem;
    bool notEnoughFunds;
    std::vector<CheckoutItem> itemAvailability;
} CheckoutResult;

typedef struct {
    QString firstName;
    QString lastName;
    QString email;
    QString address;
    QString phone;
    MoneyAmount wallet;
} AccountDetails;

typedef enum {
    ACCEPTED,
    SHIPPING,
    SHIPPED,
    REJECTED,
} OrderState;

typedef struct {
    unsigned int ID;
    OrderState state;
    MoneyAmount totalAmount;
} OrderSummary;

typedef struct {
    unsigned int ID;
    OrderState state;
    MoneyAmount totalAmount;
    std::vector<DetailedOrderItem> items;
} DetailedOrder;

typedef struct {
    QString name;
    std::vector<QString> categories;
    unsigned int maxResults;
} SearchQuery;

typedef struct {
    unsigned int ID;
    QString name;
    QPixmap icon();
    MoneyAmount price;
} Item;

typedef struct {
    QString name;
    QString description;
    std::vector<QPixmap> images;
    MoneyAmount price;
} DetailedItem;

class DataManager : public QObject
{
    Q_OBJECT
    QTcpSocket socket;

public:
    explicit DataManager(QObject *parent = nullptr);
    DataManager(unsigned int serverAddress, unsigned int serverPort);

    //Sign-in & sign-up methods
    SignUpResult signUp(SignUpData data);
    bool signIn(SignInData data, bool save);
    AutoSignInResult autoSignIn();

    //Cart-related functionality
    std::vector<DetailedCartItem> getCart();
    void addToCart(CartItem item);
    void updateCart(std::vector<CartItem> updated);
    void checkout();

    //Account-related functionality
    void getAccountDetails();
    bool updateAccountDetails(AccountDetails details);
    void getOrderHistory();
    void getOrderDetails(unsigned int ID);
    void walletDeposit(MoneyAmount amount);

    //Shop-related functionality
    void getItemList(SearchQuery query);
    void getItemData(unsigned int ID);
    void getCategories();
    ButtonId *button;


public slots:

signals:
    //Sign-in & sign-up signals
    void signUp_signal(bool result);
    void signIn_signal(bool result);

    //Cart-related signals
    void checkout_signal(CheckoutResult detailedResult);

    //Account-related signals
    void getAccountDetails_signal(AccountDetails result);
    void updateAccountDetails_signal(bool result);
    void getOrderHistory_signal(std::vector<OrderSummary> result);
    void getOrderDetails_signal(DetailedOrder result);
    void walletDeposit_signal(bool result);

    //Shop-related signals
    void getItemList_signal(std::vector<Item> result);
    void getItemData_signal(DetailedItem result);
    void getCategories_signal(std::vector<QString> result);
};


#endif // DATAMANAGER_H
