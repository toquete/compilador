TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QT += widgets

SOURCES += *.c *.h \
    gencode.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    gencode.h
