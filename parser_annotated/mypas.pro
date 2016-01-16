TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QT += widgets

SOURCES += *.c *.h

include(deployment.pri)
qtcAddDeployment()
