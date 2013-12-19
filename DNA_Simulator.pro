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
    ../../../../../Users/Zakkeri/DNA_Simulator/Source/Simulator.cpp \
    ../../../../../Users/Zakkeri/DNA_Simulator/Source/SetOfAssemblyTiles.cpp \
    ../../../../../Users/Zakkeri/DNA_Simulator/Source/AssemblyTileSetManager.cpp \
    ../../../../../Users/Zakkeri/DNA_Simulator/Source/AssemblyTile.cpp \
    ../../../../../Users/Zakkeri/DNA_Simulator/Source/ActiveTile.cpp \
    ../../../../../Users/Zakkeri/DNA_Simulator/Source/displaytile.cpp

HEADERS  += mainwindow.h \
    ../../../../../Users/Zakkeri/DNA_Simulator/Headers/Simulator.h \
    ../../../../../Users/Zakkeri/DNA_Simulator/Headers/SetOfAssemblyTiles.h \
    ../../../../../Users/Zakkeri/DNA_Simulator/Headers/AssemblyTileSetManager.h \
    ../../../../../Users/Zakkeri/DNA_Simulator/Headers/AssemblyTile.h \
    ../../../../../Users/Zakkeri/DNA_Simulator/Headers/ActiveTile.h \
    ../../../../../Users/Zakkeri/DNA_Simulator/Headers/AdditionalData.h \
    ../../../../../Users/Zakkeri/DNA_Simulator/Headers/displaytile.h

FORMS    += mainwindow.ui
