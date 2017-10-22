#-------------------------------------------------
#
# Project created by QtCreator 2017-10-22T18:53:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = editabletreemodel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treemodel.cpp \
    treeitem.cpp

HEADERS  += mainwindow.h \
    treemodel.h \
    treeitem.h

FORMS    += mainwindow.ui
