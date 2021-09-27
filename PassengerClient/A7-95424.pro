#-------------------------------------------------
#
# Project created by QtCreator 2017-05-22T11:43:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A7-95424
TEMPLATE = app


SOURCES += main.cpp\
        connectwindow.cpp \
    loginwindow.cpp \
    client_socket.cpp \
    tools.cpp \
    signup.cpp \
    interface.cpp \
    chargewin.cpp \
    ratewin.cpp \
    triprequest.cpp

HEADERS  += connectwindow.h \
    loginwindow.h \
    client_socket.h \
    network_exception.h \
    tools.h \
    signup.h \
    interface.h \
    chargewin.h \
    ratewin.h \
    triprequest.h

FORMS    += connectwindow.ui \
    loginwindow.ui \
    signup.ui \
    interface.ui \
    chargewin.ui \
    ratewin.ui \
    triprequest.ui
