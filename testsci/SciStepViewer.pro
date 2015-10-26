#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T17:20:51
#
#-------------------------------------------------

QT       += widgets

TARGET = SciStepViewer
TEMPLATE = lib

DEFINES += SCISTEPVIEWER_LIBRARY

SOURCES += SciStepViewer.cpp

HEADERS += SciStepViewer.h\
        scistepviewer_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
