#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T10:12:54
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = teleprogramma
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    edituser.cpp \
    programblock.cpp \
    addprogram.cpp \
    efirmap.cpp \
    baseparamdialog.cpp \
    mytypes.cpp \
    unittest.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    edituser.h \
    programblock.h \
    addprogram.h \
    efirmap.h \
    baseparamdialog.h \
    mytypes.h \
    unittest.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    edituser.ui \
    addprogram.ui \
    baseparamdialog.ui

RESOURCES += \
    res.qrc
