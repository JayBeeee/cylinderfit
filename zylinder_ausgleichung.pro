#-------------------------------------------------
#
# Project created by QtCreator 2014-05-31T11:08:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = zylinder_ausgleichung #name der exe
CONFIG   += console             #alle bilbiotheken für consoleneanwendung
CONFIG   -= app_bundle

TEMPLATE = app

#geklaut von openindy
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/bin/debug  #destination ordner in dem die pro datei liegt (PWD)
} else {
    DESTDIR = $$PWD/bin/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

#include path
INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/lib
INCLUDEPATH += $$PWD/lib/armadillo-4.300.6/include

INCLUDEPATH += $$PWD/lib/armadillo-4.300.6/examples/lib_win64
DEPENDPATH += $$PWD/lib/armadillo-4.300.6/examples/lib_win64
INCLUDEPATH += $$PWD/lib/armadillo-4.300.6/examples/lib_win64
DEPENDPATH += $$PWD/lib/armadillo-4.300.6/examples/lib_win64

#libs
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/armadillo-4.300.6/examples/lib_win64/ -lblas_win64_MT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/armadillo-4.300.6/examples/lib_win64/ -lblas_win64_MT

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/armadillo-4.300.6/examples/lib_win64/ -llapack_win64_MT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/armadillo-4.300.6/examples/lib_win64/ -llapack_win64_MT


SOURCES += src/main.cpp \

HEADERS += \
    lib/armadillo-4.300.6/include/armadillo

