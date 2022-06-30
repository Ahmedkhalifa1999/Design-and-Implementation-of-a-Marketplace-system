QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    buttonid.cpp \
    cart.cpp \
    datamanager.cpp \
    itemdet.cpp \
    lineedit.cpp \
    lineedit.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    shop.cpp

HEADERS += \
    account.h \
    buttonid.h \
    cart.h \
    datamanager.h \
    itemdet.h \
    lineedit.h \
    lineedit.h \
    login.h \
    mainwindow.h \
    shop.h

FORMS += \
    account.ui \
    cart.ui \
    itemdet.ui \
    login.ui \
    mainwindow.ui \
    shop.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
