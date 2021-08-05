#-------------------------------------------------
#
# Project created by QtCreator 2019-07-01T21:49:18
#
#-------------------------------------------------

QT       += core gui network sql
CONFIG += dll

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

!defined(BRAND,var){
    BRAND = ARMInspector
}

TARGET = $${BRAND}Server

VER_MAJ = 1
VER_MIN = 0
VER_PAT = 0


win32 {
    VERSION = $${VER_MAJ}.$${VER_MIN}.$$VER_PAT
}
else {
    VERSION = $$VER_MAJ\.$$VER_MIN\-$$VER_PAT
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += ARM_BRAND=\\\"$$BRAND\\\"
DEFINES += ARM_VERSION=\\\"$$VERSION\\\"
ICON = icon.ico
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        DBManager.cpp \
        MainWindow.cpp \
        ServerController.cpp

HEADERS  += MainWindow.h \
    DBManager.h \
    ServerController.h

FORMS    += MainWindow.ui

include (../libARMInspectorCore/libARMInspectorCore.pri)
include (../libRPCProtocol/libRPCProtocol.pri)

INCLUDEPATH += $$_PRO_FILE_PWD_/../libARMInspectorCore/
INCLUDEPATH += $$_PRO_FILE_PWD_/../libRPCProtocol/
