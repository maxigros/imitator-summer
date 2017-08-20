#-------------------------------------------------
#
# Project created by QtCreator 2017-08-07T01:24:39
#
#-------------------------------------------------

QT       += core gui network
CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imitator-alpha
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    common/config_storage/storage.cpp \
    common/writers/TCP/server.cpp \
    common/writers/TCP/writertcp.cpp \
    common/writers/boxwriter.cpp \
    common/writers/writergeneral.cpp \
    imitator/boxgenerate.cpp \
    imitator/datasource.cpp \
    imitator/receivers/receivergeneral.cpp

HEADERS  += mainwindow.h \
    common/config_storage/storage.h \
    common/writers/TCP/server.h \
    common/writers/TCP/writertcp.h \
    common/writers/boxwriter.h \
    common/writers/writergeneral.h \
    imitator/boxgenerate.h \
    imitator/imitator_headers.h \
    imitator/datasource.h \
    imitator/receivers/receivergeneral.h \
    imitator/receivers/receivers.h

FORMS    += mainwindow.ui
