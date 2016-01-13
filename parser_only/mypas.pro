TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += *.c *.h

include(deployment.pri)
qtcAddDeployment()
