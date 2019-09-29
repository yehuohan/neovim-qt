#-------------------------------------------------
#
# Project created by QtCreator 2019-09-28T20:29:00
#
#-------------------------------------------------

QT       += widgets
QT       += network
QT       -= gui

TARGET = treeview
TEMPLATE = lib

DEFINES += TREEVIEW_LIBRARY

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
        treeview.cpp

HEADERS += \
        treeview.h \
        $${PWD}/../../plugin_interface.h

INCLUDEPATH += \
        $${PWD}/../ \
        $${PWD}/../../ \
        $${PWD}/../../../ \
        $${PWD}/../../../auto \
        $${PWD}/../../../../third-party/msgpack-c-cpp-3.2.0/include

unix {
    target.path = /usr/lib
    INSTALLS += target
}
