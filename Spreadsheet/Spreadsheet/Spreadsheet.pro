#-------------------------------------------------
#
# Project created by QtCreator 2017-11-05T10:47:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spreadsheet
TEMPLATE = app

TRANSLATIONS = Spreadsheet_Zh_CN.ts


SOURCES += main.cpp\
        mainwindow.cpp \
    spreadsheet.cpp \
    cell.cpp \
    finddialog.cpp \
    gotocell.cpp

HEADERS  += mainwindow.h \
    spreadsheet.h \
    cell.h \
    finddialog.h \
    gotocell.h

RESOURCES += \
    Spreadsheet.qrc

FORMS += \
    gotocelldialog.ui
