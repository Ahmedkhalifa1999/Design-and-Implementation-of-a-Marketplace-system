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
#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 28142


DataManager::DataManager(QObject *parent)
    : QObject{parent}
{

}
DataManager :: DataManager(QTcpSocket *socket){
    this->socket = socket;
    socket->connectToHost(QHostAddress(SERVER_ADDRESS), SERVER_PORT);
    socket->waitForConnected();
    QObject::connect(socket, &QTcpSocket::readyRead, this, &DataManager::server_response);
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
    QRegularExpression regex("^01[0125][0-9]{8}$");
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
    if((signUpResult.validEmail == false)||(signUpResult.validPhone == false)){

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
    signUpDataObject.insert("ID", QJsonValue::fromVariant(SIGNUP_REQUEST));
    signUpDataObject.insert("Name", QJsonValue::fromVariant(data.name));
    signUpDataObject.insert("Email", QJsonValue::fromVariant(data.email));
    signUpDataObject.insert("Password", QJsonValue::fromVariant(qStringCryptPassword));
    signUpDataObject.insert("Address", QJsonValue::fromVariant(data.address));
    signUpDataObject.insert("Phone", QJsonValue::fromVariant(data.phone));

    QJsonDocument signUpJsonDoc(signUpDataObject);
    //ToJson Compact
    QByteArray signUpDataQByteArray = signUpJsonDoc.toJson(QJsonDocument::Compact);
    //writeToSocket
    qDebug()<<signUpDataQByteArray<<Qt::endl;
    qDebug()<<socket->write(signUpDataQByteArray);
    socket->flush();
    //connect Signals and Slots
    return signUpResult;
}
bool DataManager :: signIn(SignInData data, bool save){
    //Validate Email
    qDebug() << socket->bytesAvailable();
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
    signInDataObject.insert("ID", QJsonValue::fromVariant(SIGNIN_REQUEST));
    signInDataObject.insert("Email", QJsonValue::fromVariant(data.email));
    signInDataObject.insert("Password", QJsonValue::fromVariant(qStringCryptPassword));

    QJsonDocument signInJsonDoc(signInDataObject);
    //ToJson Compact
    signInDataQByteArray = signInJsonDoc.toJson(QJsonDocument::Compact);
    qDebug()<<"signIn"<<Qt::endl;

    //Send SignInData to Server
    socket->write(signInDataQByteArray);
    qDebug()<<signInDataQByteArray<<Qt::endl;
    socket->flush();

    // Save SignInData if Save = true
    saveSignin = save;

    return true;
}
SignInData DataManager :: getSignInCredentials()
{

    SignInData signInData;
    QByteArray signInQByteArray;

    if(signInfile.size()==0)
    {
        signInData.email = "";
        signInData.password = "";

        return signInData;

    }

    if(!signInfile.open(QIODevice::ReadOnly))
    {
        qCritical() << "fail";

    }
    signInQByteArray = signInfile.readAll();

    //convert to JsonDocument
    QJsonDocument signInJsonDoc = QJsonDocument::fromJson(signInQByteArray);
    // Get object from document
    QJsonObject signInJsonObj = signInJsonDoc.object();
    // Get value from object
    signInData.email = signInJsonObj.value("Email").toString();

    //Password is Hashed
    signInData.email = signInJsonObj.value("Password").toString();

    return signInData;

}


void DataManager :: getAccountDetails(){

    //Build JSON File
    QJsonObject accountDetailsObject;

    accountDetailsObject.insert("ID", QJsonValue::fromVariant(GETACCOUNTDETAILS_REQUEST));

    QJsonDocument accountDetailsJsonDoc(accountDetailsObject);
    //ToJson Compact
    QByteArray accountDetailsQByteArray = accountDetailsJsonDoc.toJson(QJsonDocument::Compact);

    //Send SignInData to Server
    socket->write(accountDetailsQByteArray);
    socket->flush();

}

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
    QJsonObject priceJsonObject;
    accountDetailsObject.insert("ID", QJsonValue::fromVariant(UPDATEACCOUNTDETAILS_REQUEST));
    accountDetailsObject.insert("Name", QJsonValue::fromVariant(details.name));
    accountDetailsObject.insert("Email", QJsonValue::fromVariant(details.email));
    accountDetailsObject.insert("Address", QJsonValue::fromVariant(details.address));
    accountDetailsObject.insert("Phone", QJsonValue::fromVariant(details.phone));
    accountDetailsObject.insert("Price", priceJsonObject);

    priceJsonObject.insert("Pounds", QJsonValue::fromVariant(details.wallet.pounds));
    priceJsonObject.insert("Piasters", QJsonValue::fromVariant(details.wallet.piasters));

    QJsonDocument accountDetailsJsonDoc(accountDetailsObject);
    //ToJson Compact
    QByteArray accountDetailsQByteArray = accountDetailsJsonDoc.toJson(QJsonDocument::Compact);
    //writeToSocket
    socket->write(accountDetailsQByteArray);
    socket->flush();
    return updateAccountResult;
}

void DataManager :: getOrderHistory()
{
    //Build JSON File
    QJsonObject orderHistoryObject;
    orderHistoryObject.insert("ID", QJsonValue::fromVariant(GETORDERHISTORY_REQUEST));

    QJsonDocument orderHistoryJsonDoc(orderHistoryObject);
    //ToJson Compact
    QByteArray orderHistoryQByteArray = orderHistoryJsonDoc.toJson(QJsonDocument::Compact);

    //Send SignInData to Server
    socket->write(orderHistoryQByteArray);
    socket->flush();
}


void DataManager :: getOrderDetails(unsigned int ID){
    //send JSON contain Request ID , orderID
    QJsonObject orderDetailsObject;

    orderDetailsObject.insert("ID", QJsonValue::fromVariant(GETORDERDETAILS_REQUEST));
    orderDetailsObject.insert("OrderID", QJsonValue::fromVariant(ID));

    QJsonDocument orderDetailsJsonDoc(orderDetailsObject);
    //ToJson Compact
    QByteArray orderDetailsQByteArray = orderDetailsJsonDoc.toJson(QJsonDocument::Compact);

    //Send SignInData to Server
    //Write to Socket
    socket->write(orderDetailsQByteArray);
    socket->flush();

}
void DataManager :: walletDeposit(MoneyAmount amount){
    //send JSON contain Request ID , Amount
    QJsonObject walletDepositObject;
    QJsonObject priceJsonObject;

    walletDepositObject.insert("ID", QJsonValue::fromVariant(WALLETDEPOSIT_REQUEST));
     walletDepositObject.insert("Price", priceJsonObject);

    priceJsonObject.insert("Pounds", QJsonValue::fromVariant(amount.pounds));
    priceJsonObject.insert("Piasters", QJsonValue::fromVariant(amount.piasters));

    QJsonDocument walletDepositJsonDoc(walletDepositObject);
    //ToJson Compact
    QByteArray walletDepositQByteArray = walletDepositJsonDoc.toJson(QJsonDocument::Compact);

    //Write to Socket
    socket->write(walletDepositQByteArray);
    socket->flush();

}

//Shop-related functionality
void DataManager :: getItemList(SearchQuery query){

    QJsonObject searchQueryObject;
    QJsonArray searchQueryArray;

    searchQueryObject.insert("ID", QJsonValue::fromVariant(GETITEMLIST_REQUEST));
    searchQueryObject.insert("Name", QJsonValue::fromVariant(query.name));
    searchQueryObject.insert("Max Results", QJsonValue::fromVariant(query.maxResults));

    for(unsigned int i = 0 ; i < query.categories.size() ; i++ ){
        searchQueryArray.insert(i ,QJsonValue::fromVariant(query.categories[i]) );
    }
    // NOT SURE
    searchQueryObject.insert("Categories", (searchQueryArray));

    QJsonDocument searchQueryJsonDoc(searchQueryObject);
    //ToJson Compact
    QByteArray searchQueryQByteArray = searchQueryJsonDoc.toJson(QJsonDocument::Compact);

    //Write to Socket
    socket->write(searchQueryQByteArray);
    socket->flush();

}
void DataManager :: getItemData(unsigned int ID){
    //send JSON contain Request ID , Amount
    QJsonObject itemDataObject;

    itemDataObject.insert("ID", QJsonValue::fromVariant(GETITEMDATA_REQUEST));
    itemDataObject.insert("ItemID", QJsonValue::fromVariant(ID));

    QJsonDocument itemDataJsonDoc(itemDataObject);
    //ToJson Compact
    QByteArray itemDataQByteArray = itemDataJsonDoc.toJson(QJsonDocument::Compact);

    //Write to Socket
    socket->write(itemDataQByteArray);
    socket->flush();

}
void DataManager :: getCategories(){
    //send JSON contain Request ID , Amount
    QJsonObject categoriesObject;

    categoriesObject.insert("ID", QJsonValue::fromVariant(GETCATEGORIES_REQUEST));

    QJsonDocument categoriesJsonDoc(categoriesObject);
    //ToJson Compact
    QByteArray categoriesQByteArray = categoriesJsonDoc.toJson(QJsonDocument::Compact);

    //Write to Socket
    socket->write(categoriesQByteArray);
    socket->flush();

}
void DataManager :: addToCart(CartItem item)
{
    //Build JSON File
    QJsonObject cartItemObject;
    cartItemObject.insert("ID", QJsonValue::fromVariant(item.ID));
    cartItemObject.insert("Quantity", QJsonValue::fromVariant(item.quantity));
    //Used to append to it many cartItemObjects
    cartItemQJsonArray.push_back(cartItemObject);
    QJsonDocument cartItemJsonDoc(cartItemQJsonArray);
    //ToJson Compact
    QByteArray cartItemQByteArray = cartItemJsonDoc.toJson(QJsonDocument::Compact);

    if(!cartfile.open(QIODevice::ReadWrite))
    {
        qCritical() << "fail";

    }

    cartfile.write(cartItemQByteArray);
    cartfile.flush();
    cartfile.close();

}
void DataManager :: updateCart(QVector<CartItem> updated){
    //Clear File Content
    cartfile.resize(0);
    //Build JSON File
    QJsonObject cartItemObject;
    unsigned i ;
    for( i = 0; i < cartItemQJsonArray.size() ; i++){
        cartItemObject.insert("ID", QJsonValue::fromVariant(updated[i].ID));
        cartItemObject.insert("Quantity", QJsonValue::fromVariant(updated[i].quantity));
        //Used to append to it many cartItemObjects
        cartItemQJsonArray[i] = cartItemObject;
    }
    for(unsigned j = i ; j < updated.size() ; j++){
        cartItemObject.insert("ID", QJsonValue::fromVariant(updated[j].ID));
        cartItemObject.insert("Quantity", QJsonValue::fromVariant(updated[j].quantity));
        //Used to append to it many cartItemObjects
        cartItemQJsonArray.push_back(cartItemObject);
    }
    QJsonDocument cartItemJsonDoc(cartItemQJsonArray);
    //ToJson Compact
    QByteArray cartItemQByteArray = cartItemJsonDoc.toJson(QJsonDocument::Compact);

    if(!cartfile.open(QIODevice::ReadWrite))
    {
        qCritical() << "fail";

    }

    cartfile.write(cartItemQByteArray);
    cartfile.flush();
    cartfile.close();
}

void DataManager::getCart(){

    QByteArray cartQByteArray;
    if(!cartfile.open(QIODevice::ReadWrite))
    {
        qCritical() << "fail";

    }

    cartQByteArray = cartfile.readAll();
    cartfile.close();
    //convert to JsonDocument
    QJsonDocument cartJsonDoc = QJsonDocument::fromJson(cartQByteArray);
    // Get object from document
    QJsonArray cartJsonArray = cartJsonDoc.array();
    QJsonObject cartJsonObj ;
    cartJsonObj.insert("ID", QJsonValue::fromVariant(GETCART_REQUEST));
    cartJsonObj.insert("Cart", cartJsonArray);
    // Get value from object

    QByteArray cartQByteArrayReq = cartJsonDoc.toJson(QJsonDocument::Compact);

    //Write to Socket
    socket->write(cartQByteArrayReq);
    socket->flush();

}

void DataManager::checkout()
{
    QByteArray cartQByteArray;
    if(!cartfile.open(QIODevice::ReadWrite))
    {
        qCritical() << "fail";

    }

    cartQByteArray = cartfile.readAll();
    cartfile.close();
    //convert to JsonDocument
    QJsonDocument cartJsonDoc = QJsonDocument::fromJson(cartQByteArray);
    // Get object from document
    QJsonArray cartJsonArray = cartJsonDoc.array();
    QJsonObject cartJsonObj ;
    cartJsonObj.insert("ID", QJsonValue::fromVariant(CHECKOUT_REQUEST));
    cartJsonObj.insert("Cart", cartJsonArray);
    // Get value from object

    QByteArray cartQByteArrayReq = cartJsonDoc.toJson(QJsonDocument::Compact);

    //Write to Socket
    socket->write(cartQByteArrayReq);
    socket->flush();

}



void DataManager :: server_response(){
    //Read Socket
    qDebug() << socket->bytesAvailable();
    QByteArray serverResponse = socket->readAll();
    qDebug() << serverResponse;
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

        //if save = true and data is valid , store in local file
        if(saveSignin && serverbooleanResponse)
        {

            if(!signInfile.open(QIODevice::ReadWrite))
            {
                qCritical() << "fail";

            }
            signInfile.write(signInDataQByteArray);
            signInfile.flush();
            signInfile.close();
        }

        emit signIn_signal(serverbooleanResponse);
        break;
    case CHECKOUT_RESPONSE:
    {

        CheckoutResult checkoutResult;
        QJsonArray serverResponseJsonArray;
        QJsonValue  jsonvalue ; // used inside loop
        CheckoutItem checkoutitem;


        checkoutResult.unavailableItem = (serverResponseJsonObj.value("Unavailable")).toBool();
        checkoutResult.notEnoughFunds = (OrderState)((serverResponseJsonObj.value("Funds")).toBool());


        serverResponseResultJsonValue = serverResponseJsonObj.value("Availability");
        // Get array from value
        serverResponseJsonArray = serverResponseResultJsonValue.toArray();
        for(unsigned int i = 0 ; i < serverResponseJsonArray.size() ; i++){
            jsonvalue = serverResponseJsonArray[i];
            checkoutitem.ID = (jsonvalue.toObject().value("Item ID")).toInt();
            checkoutitem.availableQuantity =(jsonvalue.toObject().value("Quantity")).toBool();

            checkoutResult.itemAvailability.append(checkoutitem);
        }

        emit checkout_signal(checkoutResult);


        break;
    }
    case GETACCOUNTDETAILS_RESPONSE:
    {
        //Retrieve from server struct member values
        //Pass them to signal Emitted to UI

        AccountDetails accountDetails;
        QJsonObject pricesJsonObject;

        accountDetails.name = (serverResponseJsonObj.value("Name")).toString();
        accountDetails.email =  (serverResponseJsonObj.value("Email")).toString();
        accountDetails.address =  (serverResponseJsonObj.value("Address")).toString();
        accountDetails.phone =  (serverResponseJsonObj.value("Phone")).toString();
        pricesJsonObject =  serverResponseJsonObj.value("Wallet").toObject();
        accountDetails.wallet.pounds = (pricesJsonObject.value("Pounds")).toInt();
        accountDetails.wallet.piasters = (pricesJsonObject.value("Piasters")).toInt();

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
        QJsonObject pricesJsonObject;

        // Get value from object
        serverResponseResultJsonValue = serverResponseJsonObj.value("Order History");
        // Get array from value
        serverResponseJsonArray = serverResponseResultJsonValue.toArray();
        for(unsigned int i = 0 ; i < serverResponseJsonArray.size() ; i++){
            jsonvalue = serverResponseJsonArray[i];
            Order.ID = (jsonvalue.toObject().value("Item ID")).toInt();
            Order.state =(OrderState)((jsonvalue.toObject().value("Order State")).toInt());
            pricesJsonObject = jsonvalue["Price"].toObject();
            Order.totalAmount.pounds = (pricesJsonObject.value("Pounds")).toInt();
            Order.totalAmount.piasters = (pricesJsonObject.value("Piasters")).toInt();
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
        QString encodedimage;
        QByteArray decodedimage;
        QImage image;
        QPixmap pixmap;
        QJsonObject pricesJsonObject;



        OrderDetails.ID = (serverResponseJsonObj.value("Order ID")).toInt();
        OrderDetails.state = (OrderState)((serverResponseJsonObj.value("State")).toInt());
        pricesJsonObject =  serverResponseJsonObj.value("Price").toObject();
        OrderDetails.totalAmount.pounds = (pricesJsonObject.value("Pounds")).toInt();
        OrderDetails.totalAmount.piasters = (pricesJsonObject.value("Piasters")).toInt();
        serverResponseResultJsonValue = serverResponseJsonObj.value("Items");
        // Get array from value
        serverResponseJsonArray = serverResponseResultJsonValue.toArray();
        for(unsigned int i = 0 ; i < serverResponseJsonArray.size() ; i++){
            jsonvalue = serverResponseJsonArray[i];
            item.ID = (jsonvalue.toObject().value("Name")).toInt();
            item.name = (jsonvalue.toObject().value("Name")).toString();
            pricesJsonObject = jsonvalue["Price"].toObject();
            item.price.pounds = (pricesJsonObject.value("Pounds")).toInt();
            item.price.piasters = (pricesJsonObject.value("Piasters")).toInt();
            item.quantity = (jsonvalue.toObject().value("Quantity")).toInt();

            //convert QbyteArray from document to QString
            encodedimage = (jsonvalue.toObject().value("Icon")).toString();

            // decode the base64 string to QbyteArray
            decodedimage = QByteArray::fromBase64(encodedimage.toLatin1());

            // convert to QImage
            image = QImage::fromData(decodedimage,"JPEG");
            pixmap = QPixmap::fromImage(image);
            item.icon = pixmap;

            OrderDetails.items .append(item);
        }

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
    {
        QVector <Item> ItemList;
        QJsonArray serverResponseJsonArray;
        QJsonValue  jsonvalue ; // used inside loop
        Item item;     // used inside loop
        QString encodedimage;
        QByteArray decodedimage;
        QImage image;
        QPixmap pixmap;
        QJsonObject pricesJsonObject;

        // Get value from object
        serverResponseResultJsonValue = serverResponseJsonObj.value("Items");
        // Get array from value
        serverResponseJsonArray = serverResponseResultJsonValue.toArray();
        for(unsigned int i = 0 ; i < serverResponseJsonArray.size() ; i++){
            jsonvalue = serverResponseJsonArray[i];
            item.ID = (jsonvalue.toObject().value("Item ID")).toInt();
            item.name =(jsonvalue.toObject().value("Name")).toString();
            pricesJsonObject = jsonvalue["Price"].toObject();
            item.price.pounds = (pricesJsonObject.value("Pounds")).toInt();
            item.price.piasters = (pricesJsonObject.value("Piasters")).toInt();

            //convert QbyteArray from document to QString
            encodedimage = (jsonvalue.toObject().value("Icon")).toString();

            // decode the base64 string to QbyteArray
            decodedimage = QByteArray::fromBase64(encodedimage.toLatin1());

            // convert to QImage
            image = QImage::fromData(decodedimage,"JPEG");

            //convert QImage to QPixmap
            pixmap = QPixmap::fromImage(image);
            item.icon = pixmap;

            ItemList.append(item);
        }
        emit getItemList_signal(ItemList);
        break;
    }
    case GETITEMDATA_RESPONSE :
    {
        QJsonArray serverResponseJsonArray;
        DetailedItem detailedItem;
        QString encodedimage;
        QByteArray decodedimage;
        QImage image; //
        QJsonValue  jsonvalue ; // used inside loop
        QPixmap pixmap;
        QJsonObject pricesJsonObject;


        detailedItem.name = (serverResponseJsonObj.value("Name")).toString();
        detailedItem.description = (serverResponseJsonObj.value("Description")).toString();
        pricesJsonObject = serverResponseJsonObj.value("Price").toObject();
        detailedItem.price.pounds = (pricesJsonObject.value("Pounds")).toInt();
        detailedItem.price.piasters = (pricesJsonObject.value("Piasters")).toInt();
        // Get value from object
        serverResponseResultJsonValue = serverResponseJsonObj.value("Images");
        // Get array from value
        serverResponseJsonArray = serverResponseResultJsonValue.toArray();
        for(unsigned int i = 0 ; i < serverResponseJsonArray.size() ; i++){

            //convert QbyteArray from document to QString
            encodedimage = serverResponseJsonArray[i].toString();

            // decode the base64 string to QbyteArray
            decodedimage = QByteArray::fromBase64(encodedimage.toLatin1());

            // convert to QImage
            image = QImage::fromData(decodedimage,"JPEG");

            pixmap = QPixmap::fromImage(image);


            (detailedItem.images).append(pixmap);
        }
        emit getItemData_signal( detailedItem );
        break;
    }
    case GETCATEGORIES_RESPONSE :{
        QVector <QString> categories;
        QJsonArray serverResponseJsonArray;
        QJsonValue  jsonvalue ; // used inside loop
        // Get value from object
        serverResponseResultJsonValue = serverResponseJsonObj.value("Categories");
        // Get array from value
        serverResponseJsonArray = serverResponseResultJsonValue.toArray();
        for(unsigned int i = 0 ; i < serverResponseJsonArray.size() ; i++){
            categories.append(serverResponseJsonArray[i].toString());
        }
        emit getCategories_signal(categories);
        break;
    }
    case GETCART_RESPONSE :
    {
        QVector <DetailedCartItem> cartItemList;
        QJsonArray serverResponseJsonArray;
        QJsonValue  jsonvalue ; // used inside loop
        DetailedCartItem cartitem;     // used inside loop
        QString encodedimage;
        QByteArray decodedimage;
        QImage image;
        QPixmap pixmap;

        // Get value from object
        serverResponseResultJsonValue = serverResponseJsonObj.value("Items");
        // Get array from value
        serverResponseJsonArray = serverResponseResultJsonValue.toArray();
        for(unsigned int i = 0 ; i < serverResponseJsonArray.size() ; i++){
            jsonvalue = serverResponseJsonArray[i];
            cartitem.name =(jsonvalue.toObject().value("name")).toString();
            cartitem.price.pounds = (jsonvalue.toObject().value("Pound")).toInt();
            cartitem.price.piasters = (jsonvalue.toObject().value("Piasters")).toInt();
            cartitem.quantity = (jsonvalue.toObject().value("Quantity")).toInt();

            //convert QbyteArray from document to QString
            encodedimage = (jsonvalue.toObject().value("Icon")).toString();

            // decode the base64 string to QbyteArray
            decodedimage = QByteArray::fromBase64(encodedimage.toLatin1());

            // convert to QImage
            image = QImage::fromData(decodedimage,"JPEG");
            pixmap = QPixmap::fromImage(image);
            cartitem.icon = pixmap;
            cartItemList.append(cartitem);
        }
        emit getCart_signal(cartItemList);
        break;
    }
    }

}
