#include "datamanager.h"
#include <QHostAddress>
#include <QJsonObject>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QByteArray>




DataManager::DataManager(QObject *parent)
    : QObject{parent}
{

}
DataManager :: DataManager(unsigned int serverAddress, unsigned int serverPort){
    //convert to string

    QString serverAddressString  = QString::number(serverAddress);
    socket.connectToHost(QHostAddress(serverAddressString), serverPort);
}
bool validate_Email(const QString email)
{
    bool result = true;
    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z][-._+])[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)([0-9a-zA-Z][.])[a-zA-Z]{2,6}$");
    if(!regex.match(email).hasMatch())
    {
        result = false;
    }

    return result;
}

bool validate_Phone(const QString phone)
{

    bool result = true;
    QRegularExpression regex("+20(10|11|12|15)[0-9]{8}");
    if(!regex.match(phone).hasMatch())
    {
        result = false;
    }
    return result;
}



SignUpResult  DataManager :: signUp  (SignUpData data){
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

    QJsonObject signUpDataObject;
    signUpDataObject.insert("RequestID", QJsonValue::fromVariant(SIGNUP_REQUEST));
    signUpDataObject.insert("FirstName", QJsonValue::fromVariant(data.firstName));
    signUpDataObject.insert("LastName", QJsonValue::fromVariant(data.lastName));
    signUpDataObject.insert("Email", QJsonValue::fromVariant(data.email));
    //hashing
    //recordObject.insert("Password", QJsonValue::fromVariant(data.password));
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


void DataManager :: server_response(){
    //Read Socket
    QByteArray serverResponse = socket.readAll();
    //convert to JsonDocument
    QJsonDocument serverJsonResponse = QJsonDocument::fromJson(serverResponse);
    // Get QVarient
    QVariant serverQvariant = serverJsonResponse.toVariant();
    QMap serverQmap = serverQvariant.toMap();
    //Extract ID
    int serverResponseID = serverQmap["ID"].toInt();
    bool serverbooleanResponse ;
    switch (serverResponseID){
    //ID for which Request
    case SIGNUP_RESPONSE:
        //Extract Result
        serverbooleanResponse = serverQmap["Result"].toBool();
        emit signUp_signal(serverbooleanResponse);
        break;
    case SIGNIN_RESPONSE:
        //Extract Result
        serverbooleanResponse = serverQmap["Result"].toBool();
        emit signIn_signal(serverbooleanResponse);
        break;
    case WALLETDEPOSIT_RESPONSE:
        //Extract Result
        serverbooleanResponse = serverQmap["Result"].toBool();
        emit walletDeposit_signal(serverbooleanResponse);
        break;
    }
}


