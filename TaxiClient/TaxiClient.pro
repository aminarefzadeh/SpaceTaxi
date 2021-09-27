#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T14:05:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TaxiClient
TEMPLATE = app


SOURCES += main.cpp\
    client_socket.cpp \
    tools.cpp \
    signup.cpp \
    loginwindow.cpp \
    interface.cpp \
    setstatus.cpp \
    acceptrequest.cpp \
    showrequests.cpp \
    currenttrip.cpp \
    connectwindow.cpp

HEADERS  += \
    client_socket.h \
    network_exception.h \
    tools.h \
    signup.h \
    loginwindow.h \
    interface.h \
    setstatus.h \
    acceptrequest.h \
    showrequests.h \
    currenttrip.h \
    connectwindow.h

FORMS    += \
    signup.ui \
    loginwindow.ui \
    interface.ui \
    setstatus.ui \
    acceptrequest.ui \
    showrequests.ui \
    currenttrip.ui \
    connectwindow.ui

DISTFILES +=
