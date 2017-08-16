#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T18:04:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtSmartCalendar
TEMPLATE = app
TRANSLATIONS += cn.ts

SOURCES += main.cpp\
    logindialog.cpp \
    calendar.cpp \
    querydialog.cpp \
    additemdialog.cpp \
    usermanager.cpp \
    file.cpp \
    thing.cpp \
    dragablelistwidget.cpp \
    mainwindow.cpp \
    classtable.cpp \
    classlabel.cpp \
    timelabel.cpp \
    classitem.cpp \
    classmanager.cpp \
    addclassdialog.cpp

HEADERS  += \
    logindialog.h \
    calendar.h \
    querydialog.h \
    additemdialog.h \
    usermanager.h \
    file.h \
    thing.h \
    dragablelistwidget.h \
    mainwindow.h \
    classtable.h \
    classlabel.h \
    timelabel.h \
    classitem.h \
    classmanager.h \
    addclassdialog.h

FORMS    += \
    logindialog.ui \
    querydialog.ui \
    additemdialog.ui \
    classtable.ui \
    addclassdialog.ui \
    classmanager.ui

RESOURCES += icons.qrc \

DISTFILES +=

