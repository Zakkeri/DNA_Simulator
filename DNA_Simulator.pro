#-------------------------------------------------
#
# Project created by QtCreator 2013-05-26T13:12:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DNA_Simulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Source/Simulator.cpp \
    Source/SetOfAssemblyTiles.cpp \
    Source/AssemblyTileSetManager.cpp \
    Source/AssemblyTile.cpp \
    Source/ActiveTile.cpp \
    Source/displaytile.cpp

HEADERS  += mainwindow.h \
    Headers/Simulator.h \
    Headers/SetOfAssemblyTiles.h \
    Headers/AssemblyTileSetManager.h \
    Headers/AssemblyTile.h \
    Headers/ActiveTile.h \
    Headers/AdditionalData.h \
    Headers/displaytile.h

FORMS    += mainwindow.ui
