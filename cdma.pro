#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T12:02:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS +=-L$$quote(D:\Program Files\MariaDB 10.1\lib) -llibmysql
INCLUDEPATH +=$$quote(D:\Program Files\MariaDB 10.1\include\mysql)
TARGET = cdma
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindlg.cpp \
    scriptdlg.cpp \
    mymysql.cpp

HEADERS  += mainwindow.h \
    logindlg.h \
    scriptdlg.h \
    mymysql.h
