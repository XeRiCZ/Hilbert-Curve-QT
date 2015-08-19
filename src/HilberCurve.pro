#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T14:41:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HilberCurve
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Curve.cpp \
    Drawer.cpp \
    HilbertCurve.cpp \
    SierpinskiCurve.cpp \
    Vector2.cpp

HEADERS  += mainwindow.h \
    Curve.h \
    Drawer.h \
    HilbertCurve.h \
    SierpinskiCurve.h \
    Vector2.h

FORMS    += mainwindow.ui
