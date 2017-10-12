#-------------------------------------------------
#
# Project created by QtCreator 2017-10-08T23:12:38
#
#-------------------------------------------------

QT       += core gui
QT +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myqq
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    toolbox1.cpp \
    logindlg.cpp

HEADERS  += widget.h \
    toolbox1.h \
    logindlg.h

RESOURCES += \
    myqq.qrc
