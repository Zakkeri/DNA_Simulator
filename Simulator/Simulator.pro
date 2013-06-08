#-------------------------------------------------
#
# Project created by QtCreator 2013-06-06T17:52:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../Source/Simulator.cpp \
    ../Source/SetOfAssemblyTiles.cpp \
    ../Source/AssemblyTileSetManager.cpp \
    ../Source/AssemblyTile.cpp \
    ../Source/ActiveTile.cpp

HEADERS  += mainwindow.h \
    ../Headers/Simulator.h \
    ../Headers/SetOfAssemblyTiles.h \
    ../Headers/AssemblyTileSetManager.h \
    ../Headers/AssemblyTile.h \
    ../Headers/ActiveTile.h

FORMS    += mainwindow.ui
