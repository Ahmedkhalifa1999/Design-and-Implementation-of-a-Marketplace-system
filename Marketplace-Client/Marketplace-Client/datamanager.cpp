#include "datamanager.h"
#include <QHostAddress>
#include <QJsonObject>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>
#include <QJsonArray>
#include <QJsonValue>


DataManager::DataManager(QObject *parent)
    : QObject{parent}
{

}
DataManager :: DataManager(unsigned int serverAddress, unsigned int serverPort){
    //convert to string

    QString serverAddressString  = QString::number(serverAddress);
    socket.connectToHost(QHostAddress(serverAddressString), serverPort);
    QObject::connect(&socket, &QTcpSocket::bytesWritten, this, &DataManager::server_response);
}
bool DataManager :: validate_Email(const QString email)
{
    bool result = true;
    QRegularExpression regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if(!regex.match(email).hasMatch())
    {
        result = false;
    }

    return result;
}

bool DataManager :: validate_Phone(const QString phone)
{

    bool result = true;
    QRegularExpression regex("^((\\+?(\\d{2}))\\s?)?((\\d{2})|(\\((\\d{2})\\))\\s?)?(\\d{3,15})(\\-(\\d{3,15}))?$");
    if(!regex.match(phone).hasMatch())
    {
        result = false;
    }
    return result;
}

SignUpResult DataManager :: signUp  (SignUpData data){
    SignUpResult signUpResult;

    if(validate_Email(data.email))
    {
        signUpResult.validEmail = true;
    }
    else
    {
        signUpResult.validEmail = false;

    }

    if(validate_Phone(data.phone))
    {
        signUpResult.validPhone = true;
    }
    else
    {
        signUpResult.validPhone = false;
    }
    if((signUpResult.validEmail == false)||(signUpResult.validPhone = false)){

        return signUpResult;
    }
    //hashing
    QCryptographicHash qCryptPassword = QCryptographicHash(QCryptographicHash::Sha3_256);
    //from Qstring to QByteArray (not encrypted)
    QByteArray qBytePassword = (data.password).toUtf8();
    // Encrypting the QByteArray format of password
    QByteArray qByteCryptPassword = QCryptographicHash::hash(qBytePassword , QCryptographicHash::Sha3_256);
    //from QByteArray to Qstring (encrypted)
    QString qStringCryptPassword =  QString::fromUtf8(qByteCryptPassword);


    //Build JSON File
    QJsonObject signUpDataObject;
    signUpDataObject.insert("RequestID", QJsonValue::fromVariant(SIGNUP_REQUEST));
    signUpDataObject.insert("FirstName", QJsonValue::fromVariant(data.firstName));
    signUpDataObject.insert("LastName", QJsonValue::fromVariant(data.lastName));
    signUpDataObject.insert("Email", QJsonValue::fromVariant(data.email));
    signUpDataObject.insert("Password", QJsonValue::fromVariant(qStringCryptPassword));
    signUpDataObject.insert("Address", QJsonValue::fromVariant(data.address));
    signUpDataObject.insert("Phone", QJsonValue::fromVariant(data.phone));

    QJsonDocument signUpJsonDoc(signUpDataObject);
    //ToJson Compact
    QByteArray signUpDataQByteArray = signUpJsonDoc.toJson(QJsonDocument::Compact);
    //writeToSocket
    socket.write(signUpDataQByteArray);

    //connect Signals and Slots
    return signUpResult;
}
bool DataManager :: signIn(SignInData data, bool save){
    //Validate Email
    if(!validate_Email(data.email))
    {
        return false;
    }
    //Hashing
    QCryptographicHash qCryptPassword = QCryptographicHash(QCryptographicHash::Sha3_256);
    //from Qstring to QByteArray (not encrypted)
    QByteArray qBytePassword = (data.password).toUtf8();
    // Encrypting the QByteArray format of password
    QByteArray qByteCryptPassword = QCryptographicHash::hash(qBytePassword , QCryptographicHash::Sha3_256);
    //from QByteArray to Qstring (encrypted)
    QString qStringCryptPassword =  QString::fromUtf8(qByteCryptPassword);

    //Build JSON File
    QJsonObject signInDataObject;
    signInDataObject.insert("RequestID", QJsonValue::fromVariant(SIGNIN_REQUEST));
    signInDataObject.insert("Email", QJsonValue::fromVariant(data.email));
    signInDataObject.insert("Password", QJsonValue::fromVariant(qStringCryptPassword));

    QJsonDocument signInJsonDoc(signInDataObject);
    //ToJson Compact
    QByteArray signInDataQByteArray = signInJsonDoc.toJson(QJsonDocument::Compact);

    //Send SignInData to Server
    socket.write(signInDataQByteArray);
    // Save SignInData if Save = true
    return true;
}
void DataManager :: getAccountDetails(){

    //Build JSON File
    QJsonObject accountDetailsObject;
    accountDetailsObject.insert("RequestID", QJsonValue::fromVariant(GETACCOUNTDETAILS_REQUEST));

    QJsonDocument accountDetailsJsonDoc(accountDetailsObject);
    //ToJson Compact
    QByteArray accountDetailsQByteArray = accountDetailsJsonDoc.toJson(QJsonDocument::Compact);

    //Send SignInData to Server
    socket.write(accountDetailsQByteArray);

}

//mehtaga hagat mn el cart fa hasebha dlw2ty
/*void DataManager :: checkout(){
// Send checkout Request
 //Check available fund
}*/

UpdateAccountResult DataManager :: updateAccountDetails(AccountDetails details){
    // Validate phone and email
    UpdateAccountResult  updateAccountResult;

    if(validate_Email(details.email))
    {
        updateAccountResult.validEmail = true;
    }
    else
    {
        updateAccountResult.validEmail = false;

    }
    if(validate_Phone(details.phone))
    {
        updateAccountResult.validPhone = true;
    }
    else
    {
        updateAccountResult.validPhone = false;
    }
    if((updateAccountResult.validEmail == false)||(updateAccountResult.validPhone = false)){

        return updateAccountResult;
    }

    // Build JSON file
    QJsonObject accountDetailsObject;
    accountDetailsObject.insert("RequestID", QJsonValue::fromVariant(UPDATEACCOUNTDETAILS_REQUEST));
    accountDetailsObject.insert("FirstName", QJsonValue::fromVariant(details.firstName));
    accountDetailsObject.insert("LastName", QJsonValue::fromVariant(details.lastName));
    accountDetailsObject.insert("Email", QJsonValue::fromVariant(details.email));
    accountDetailsObject.insert("Address", QJsonValue::fromVariant(details.address));
    accountDetailsObject.insert("Phone", QJsonValue::fromVariant(details.phone));
    accountDetailsObject.insert("Pounds", QJsonValue::fromVariant(details.wallet.pounds));
    accountDetailsObject.insert("Piasters", QJsonValue::fromVariant(details.wallet.piasters));

    QJsonDocument accountDetailsJsonDoc(accountDetailsObject);
    //ToJson Compact
    QByteArray accountDetailsQByteArray = accountDetailsJsonDoc.toJson(QJsonDocument::Compact);
    //writeToSocket
    socket.write(accountDetailsQByteArray);
    return updateAccountResult;
}

void DataManager :: getOrderHistory()
{
    //Build JSON File
    QJsonObject orderHistoryObject;
    orderHistoryObject.insert("RequestID", QJsonValue::fromVariant(GETORDERHISTORY_REQUEST));

    QJsonDocument orderHistoryJsonDoc(orderHistoryObject);
    //ToJson Compact
    QByteArray orderHistoryQByteArray = orderHistoryJsonDoc.toJson(QJsonDocument::Compact);

    //Send SignInData to Server
    socket.write(orderHistoryQByteArray);
}


void DataManager :: getOrderDetails(unsigned int ID){
    //send JSON contain Request ID , orderID
    QJsonObject orderDetailsObject;

    orderDetailsObject.insert("RequestID", QJsonValue::fromVariant(GETORDERDETAILS_REQUEST));
    orderDetailsObject.insert("OrderID", QJsonValue::fromVariant(ID));

    QJsonDocument orderDetailsJsonDoc(orderDetailsObject);
    //ToJson Compact
    QByteArray orderDetailsQByteArray = orderDetailsJsonDoc.toJson(QJsonDocument::Compact);

    //Send SignInData to Server
    //Write to Socket
    socket.write(orderDetailsQByteArray);
}
void DataManager :: walletDeposit(MoneyAmount amount){
    //send JSON contain Request ID , Amount
    QJsonObject walletDepositObject;

    walletDepositObject.insert("RequestID", QJsonValue::fromVariant(WALLETDEPOSIT_REQUEST));
    walletDepositObject.insert("Pounds", QJsonValue::fromVariant(amount.pounds));
    walletDepositObject.insert("Piasters", QJsonValue::fromVariant(amount.piasters));

    QJsonDocument walletDepositJsonDoc(walletDepositObject);
    //ToJson Compact
    QByteArray walletDepositQByteArray = walletDepositJsonDoc.toJson(QJsonDocument::Compact);

    //Write to Socket
    socket.write(walletDepositQByteArray);
}

//Shop-related functionality
void DataManager :: getItemList(SearchQuery query){

    /* typedef struct {
        QString name;
        QVector<QString> categories;
        unsigned int maxResults;
    } SearchQuery;*/
    //send JSON contain Request ID , Amount
    QJsonObject searchQueryObject;
    QJsonArray searchQueryArray;

    searchQueryObject.insert("RequestID", QJsonValue::fromVariant(GETITEMLIST_REQUEST));
    searchQueryObject.insert("Name", QJsonValue::fromVariant(query.name));
    searchQueryObject.insert("MaxResult", QJsonValue::fromVariant(query.maxResults));

    for(unsigned int i = 0 ; i < query.categories.size() ; i++ ){
        searchQueryArray.insert(i ,QJsonValue::fromVariant(query.categories[i]) );
    }
    // NOT SURE
    searchQueryObject.insert("Category", (searchQueryArray));

    QJsonDocument searchQueryJsonDoc(searchQueryObject);
    //ToJson Compact
    QByteArray searchQueryQByteArray = searchQueryJsonDoc.toJson(QJsonDocument::Compact);

    //Write to Socket
    socket.write(searchQueryQByteArray);
}
/*void DataManager :: getItemData(unsigned int ID);
void DataManager :: getCategories();
*/

void DataManager :: server_response(qint64 bytes){
    //Read Socket
    QByteArray serverResponse = socket.readAll();
    //convert to JsonDocument
    QJsonDocument serverResponseJsonDoc = QJsonDocument::fromJson(serverResponse);
    // Get object from document
    QJsonObject serverResponseJsonObj = serverResponseJsonDoc.object();
    // Get value from object
    QJsonValue serverResponseIDJsonValue = serverResponseJsonObj.value("ID");
    QJsonValue serverResponseResultJsonValue;

    unsigned int serverResponseID = serverResponseIDJsonValue.toInt();
    bool serverbooleanResponse;

    switch (serverResponseID){
    //ID for which Request
    case SIGNUP_RESPONSE:
        //Retrieve the Result from Server
        serverResponseResultJsonValue = serverResponseJsonObj.value("Result");
        serverbooleanResponse = serverResponseResultJsonValue.toBool();
        emit signUp_signal(serverbooleanResponse);
        break;
    case SIGNIN_RESPONSE:
        //Retrieve the Result from Server
        serverResponseResultJsonValue = serverResponseJsonObj.value("Result");
        serverbooleanResponse = serverResponseResultJsonValue.toBool();
        emit signIn_signal(serverbooleanResponse);
        break;
    case GETACCOUNTDETAILS_RESPONSE:
    {
        //Retrieve from server struct member values
        //Pass them to signal Emitted to UI

        AccountDetails accountDetails;

        accountDetails.firstName = (serverResponseJsonObj.value("FirstName")).toString();
        accountDetails.lastName = (serverResponseJsonObj.value("LastName")).toString();
        accountDetails.email =  (serverResponseJsonObj.value("Email")).toString();
        accountDetails.address =  (serverResponseJsonObj.value("Address")).toString();
        accountDetails.phone =  (serverResponseJsonObj.value("Phone")).toString();
        accountDetails.wallet.pounds =  (serverResponseJsonObj.value("Pounds")).toInt();
        accountDetails.wallet.piasters = (serverResponseJsonObj.value("Piasters")).toInt();

        //emit signal to UI
        emit getAccountDetails_signal(accountDetails);
        break;
    }
    case UPDATEACCOUNTDETAILS_RESPONSE:
        //Retrieve the Result from Server
        serverResponseResultJsonValue = serverResponseJsonObj.value("Result");
        serverbooleanResponse = serverResponseResultJsonValue.toBool();
        emit updateAccountDetails_signal(serverbooleanResponse);
        break;
    case GETORDERHISTORY_RESPONSE :
    {
        QVector <OrderSummary> OrderHistory;
        QJsonArray serverResponseJsonArray;
        QJsonValue  jsonvalue ; // used inside loop
        OrderSummary Order;     // used inside loop
        // Get value from object
        serverResponseResultJsonValue = serverResponseJsonObj.value("OrderHistory");
        // Get array from value
        serverResponseJsonArray = serverResponseResultJsonValue.toArray();
        for(unsigned int i = 0 ; i < serverResponseJsonArray.size() ; i++){
            Order.ID = (jsonvalue.toObject().value("ID")).toInt();
            Order.state =(OrderState)((jsonvalue.toObject().value("state")).toInt());
            Order.totalAmount.pounds = (jsonvalue.toObject().value("Pound")).toInt();
            Order.totalAmount.piasters = (jsonvalue.toObject().value("Piasters")).toInt();
            OrderHistory.append(Order);
        }
        emit getOrderHistory_signal(OrderHistory);
        break;
    }
    case GETORDERDETAILS_RESPONSE:
    {
        DetailedOrder OrderDetails;
        QJsonArray serverResponseJsonArray;
        QJsonValue  jsonvalue ; // used inside loop
        DetailedOrderItem item;
        QVector<DetailedOrderItem> items;



        OrderDetails.ID = (serverResponseJsonObj.value("OrderID")).toInt();
        OrderDetails.state = (OrderState)((serverResponseJsonObj.value("State")).toInt());
        OrderDetails.totalAmount.pounds =(serverResponseJsonObj.value("Pounds")).toInt();
        OrderDetails.totalAmount.piasters =  (serverResponseJsonObj.value("Piasters")).toInt();
        serverResponseResultJsonValue = serverResponseJsonObj.value("Items");
        // Get array from value
        serverResponseJsonArray = serverResponseResultJsonValue.toArray();
        for(unsigned int i = 0 ; i < serverResponseJsonArray.size() ; i++){
            item.name = (jsonvalue.toObject().value("Name")).toString();
            item.price.pounds =(jsonvalue.toObject().value("Pounds")).toInt();
            item.price.piasters =(jsonvalue.toObject().value("Piasters")).toInt();
            item.quantity = (jsonvalue.toObject().value("Quantity")).toInt();
            //icons
            items.append(item);
        }
        OrderDetails.items = items;
        emit getOrderDetails_signal(OrderDetails);

        break;
    }
    case WALLETDEPOSIT_RESPONSE:
        //Extract Result
        serverResponseResultJsonValue = serverResponseJsonObj.value("Result");
        serverbooleanResponse = serverResponseResultJsonValue.toBool();
        emit walletDeposit_signal(serverbooleanResponse);
        break;

    case GETITEMLIST_RESPONSE:
        break;
    }
}
