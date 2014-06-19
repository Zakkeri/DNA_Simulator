#ifndef BASE_SIMULATOR_H
#define BASE_SIMULATOR_H
#include <QList>
#include <QMap>
#include"../Headers/SetOfAssemblyTiles.h"
#include "../Headers/displaytile2.h"

//Abstract class for different types of simulators
class Base_Simulator
{
public:
    //Initialize simulator
    virtual void initialize() = 0;

    //Begin simulation
    virtual void startSimulation() = 0;

    //Converts Assembly tile into Display tile, returns it as a list of display tiles
    virtual QList<DisplayTile *> toDisplayTile(AssemblyTile * T) = 0;

    //Get the list of all sets of assembly tiles
    virtual QList<SetOfAssemblyTiles *> &getAssemblies() = 0;

};

#endif // BASE_SIMULATOR_H
