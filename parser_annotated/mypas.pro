TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QT += widgets

SOURCES += *.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += *.h
