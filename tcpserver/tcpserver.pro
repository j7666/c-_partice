QT += core network
QT -= gui

CONFIG += c++11

TARGET = tcpserver
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tcpreceive.cpp

HEADERS += \
    tcpreceive.h \
    pub.h
