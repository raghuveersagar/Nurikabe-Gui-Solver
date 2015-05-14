#-------------------------------------------------
#
# Project created by QtCreator 2014-05-10T20:33:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nurikabe
TEMPLATE = app


SOURCES += \
    mymodel.cpp \
    nurikabe.cpp \
    puzzle.cpp \
    fsdialog.cpp \
    mainwindow.cpp \
    Nurikabe_main.cpp



HEADERS  += \
    mymodel.h \
    nurikabe.h \
    puzzle.h \
    fsdialog.h \
    mainwindow.h



FORMS    += mainwindow.ui

CONFIG += c++11
