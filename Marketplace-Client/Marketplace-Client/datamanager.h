#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QTcpSocket>
#include "buttonid.h"
#include "lineedit.h"

#include <QVector>
#include <QFile>
#include <QJsonArray>

#define SIGNUP_REQUEST                0
#define SIGNUP_RESPONSE               1

#define SIGNIN_REQUEST                2
#define SIGNIN_RESPONSE               3

#define CHECKOUT_REQUEST              4
#define CHECKOUT_RESPONSE             5

#define GETACCOUNTDETAILS_REQUEST     6
#define GETACCOUNTDETAILS_RESPONSE    7

#define UPDATEACCOUNTDETAILS_REQUEST  8
#define UPDATEACCOUNTDETAILS_RESPONSE 9

#define GETORDERHISTORY_REQUEST       10
#define GETORDERHISTORY_RESPONSE      11

#define GETORDERDETAILS_REQUEST       12
#define GETORDERDETAILS_RESPONSE      13

#define WALLETDEPOSIT_REQUEST         14
#define WALLETDEPOSIT_RESPONSE        15

#define GETITEMLIST_REQUEST           16
#define GETITEMLIST_RESPONSE          17

#define GETITEMDATA_REQUEST           18
#define GETITEMDATA_RESPONSE          19

#define GETCATEGORIES_REQUEST         20
#define GETCATEGORIES_RESPONSE        21

#define GETCART_REQUEST               22
#define GETCART_RESPONSE              23

typedef struct {
    unsigned int pounds;
    unsigned int piasters;
} MoneyAmount;

typedef struct {
    QString name;

    QString email;
    QString password;
    QString address;
    QString phone;
} SignUpData;

typedef struct {
    bool validEmail;
    bool validPhone;
} SignUpResult, UpdateAccountResult;

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
    bool availableQuantity;
} CheckoutItem;

typedef struct {
    bool unavailableItem;
    bool notEnoughFunds;
    QVector<CheckoutItem> itemAvailability;
} CheckoutResult;

typedef struct {
    QString name;

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
    QString name;
    QPixmap icon;
    MoneyAmount price;
} Item;

typedef struct {
    unsigned int ID;
    QString name;
    QPixmap icon;
    MoneyAmount price;
    unsigned int quantity;
} DetailedCartItem, DetailedOrderItem;

typedef struct {
    unsigned int ID;
    OrderState state;
    MoneyAmount totalAmount;
} OrderSummary;

typedef struct {
    unsigned int ID;
    OrderState state;
    MoneyAmount totalAmount;
    QVector<DetailedOrderItem> items;
} DetailedOrder;

typedef struct {
    QString name;
    QVector<QString> categories;
    unsigned int maxResults;
} SearchQuery;

typedef struct {
    QString name;
    QString description;
    QVector<QPixmap> images;
    MoneyAmount price;
} DetailedItem;

class DataManager : public QObject
{
    Q_OBJECT
    QTcpSocket socket;
    //Global Variables
    QFile signInfile;
    QFile cartfile;
    QFile itemfile;
    QByteArray signInDataQByteArray; //variable to store signIn Data
    QJsonArray cartItemQJsonArray;   //
    bool saveSignin;

public:
    explicit DataManager(QObject *parent = nullptr);
    DataManager(unsigned int serverAddress, unsigned int serverPort);

    //Sign-in & sign-up methods
    SignUpResult signUp(SignUpData data);
    bool signIn(SignInData data, bool save);
    AutoSignInResult autoSignIn();

    //Cart-related functionality
    void getCart();
    void addToCart(CartItem item);
    void updateCart(QVector<CartItem> updated);
    void checkout();
   LineEdit *quant;
    //Account-related functionality
    void getAccountDetails();
    UpdateAccountResult updateAccountDetails(AccountDetails details);
    void getOrderHistory();
    void getOrderDetails(unsigned int ID);
    void walletDeposit(MoneyAmount amount);

    //Shop-related functionality
    void getItemList(SearchQuery query);
    void getItemData(unsigned int ID);
    void getCategories();
    ButtonId *button;


    //Helper functions in SignUp and SignIn
    bool validate_Email(const QString email);
    bool validate_Phone(const QString phone);

public slots:

    void server_response(qint64 bytes);
    //slot process the signal emitted from server


signals:
    //Sign-in & sign-up signals
    void signUp_signal(bool result);
    void signIn_signal(bool result);

    //Cart-related signals
    void checkout_signal(CheckoutResult detailedResult);
    void getCart_signal(QVector<DetailedCartItem> result);

    //Account-related signals
    void getAccountDetails_signal(AccountDetails result);
    void updateAccountDetails_signal(bool result);
    void getOrderHistory_signal(QVector<OrderSummary> result);
    void getOrderDetails_signal(DetailedOrder result);
    void walletDeposit_signal(bool result);

    //Shop-related signals
    void getItemList_signal(QVector<Item> result);
    void getItemData_signal(DetailedItem result);
    void getCategories_signal(QVector<QString> result);
};


#endif // DATAMANAGER_H
