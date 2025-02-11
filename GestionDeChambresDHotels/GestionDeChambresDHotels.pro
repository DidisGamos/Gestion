QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    admin.cpp \
    ajoutadmin.cpp \
    ajoutgerant.cpp \
    centerdelegate.cpp \
    client.cpp \
    login.cpp \
    loginn.cpp \
    main.cpp \
    mainwindowgerant.cpp \
    modifhotel.cpp

HEADERS += \
    account.h \
    admin.h \
    ajoutadmin.h \
    ajoutgerant.h \
    baseDeDonnees.h \
    centerdelegate.h \
    client.h \
    login.h \
    loginn.h \
    mainwindowgerant.h \
    modifhotel.h

FORMS += \
    account.ui \
    admin.ui \
    ajoutadmin.ui \
    ajoutgerant.ui \
    client.ui \
    login.ui \
    loginn.ui \
    mainwindowgerant.ui \
    modifhotel.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=


RESOURCES += \
    ressource.qrc
