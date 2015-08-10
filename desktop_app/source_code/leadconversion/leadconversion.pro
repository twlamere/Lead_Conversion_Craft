#-------------------------------------------------
#
# Project created by QtCreator 2015-07-30T14:37:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = leadconversion
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    toxml.cpp \
    tocsv.cpp

HEADERS  += mainwindow.h \
    toxml.h \
    tocsv.h

FORMS    += mainwindow.ui

RESOURCES += \
    ../QDarkStyleSheet-master/qdarkstyle/style.qrc

DISTFILES += \
    ../QDarkStyleSheet-master/qdarkstyle/style.qss \
    ../QDarkStyleSheet-master/qdarkstyle/rc/* \
    whitelogo.png

CONFIG += c++11
