TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += *.c *.h \
    errorhandler.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    errorhandler.h
