#-------------------------------------------------
#
# Project created by QtCreator 2017-02-15T16:09:07
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fealizer
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
    equalizer.cpp \
    filter.cpp \
    feafilter/filt.cpp

HEADERS  += mainwindow.h \
    equalizer.h \
    feafilter/filt.h

FORMS    += mainwindow.ui

win32 {
    INCLUDEPATH += $$PWD/SFML/include
    LIBS += -L"$$PWD/SFML/lib" -lsfml-audio-d -lsfml-system-d -lsfml-window-d -lsfml-graphics-d
}

linux-g++ {
    LIBS += -lsfml-audio -lsfml-system
}
