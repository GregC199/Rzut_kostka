#-------------------------------------------------
#
# Project created by QtCreator 2020-05-14T19:56:04
#
#-------------------------------------------------

QT       += core gui

#polaczenie uart
QT += bluetooth
#wykresy
QT += charts
#kosc
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WDS_Kosc_Linux
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS



# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    bluetooth.cpp \
    diody.cpp \
    kosc.cpp \
    main.cpp \
    mainwindow.cpp \
    wizualizacjakosc.cpp \
    wykres.cpp \
    wykresy.cpp

HEADERS += \
    mainwindow.h \
    wizualizacjakosc.h \
    wykres.h

FORMS += \
    mainwindow.ui

SUBDIRS += \
    WDS_Kosc_Linux.pro
