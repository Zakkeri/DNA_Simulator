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
    Source/SetOfAssemblyTiles.cpp \
    Source/AssemblyTileSetManager.cpp \
    Source/AssemblyTile.cpp \
    Source/ActiveTile.cpp \
    Source/displaytile2.cpp \
    mygraphicsview.cpp \
    Source/Simulator_2HAM.cpp \
    Source/base_simulator.cpp \
    Source/Simulator_aTAM.cpp

HEADERS  += mainwindow.h \
    Headers/SetOfAssemblyTiles.h \
    Headers/AssemblyTileSetManager.h \
    Headers/AssemblyTile.h \
    Headers/ActiveTile.h \
    Headers/AdditionalData.h \
    Headers/displaytile2.h \
    mygraphicsview.h \
    Headers/Simulator_2HAM.h \
    Headers/base_simulator.h \
    Headers/Simulator_aTAM.h


FORMS    += mainwindow.ui
