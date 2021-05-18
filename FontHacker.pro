QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CFLAGS += -fPIC -Wall -Werror -O2

INCLUDEPATH += \
../../GamesProjects/libGamesEngines/Cpp11

LIBS += -L../../GamesProjects/objs -lGamesEngines -llua

SOURCES += \
    Widget_BitmapFont.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    Widget_BitmapFont.h

FORMS += \
    MainWindow.ui