#ifndef _SIMULATOR_H
#define _SIMULATOR_H
#include"../Headers/SetOfAssemblyTiles.h"
#include"../Headers/AssemblyTileSetManager.h"
#include "../Headers/displaytile2.h"
#include<QMap>
#include<QString>
//#define DEBUG
typedef struct fittingSpot
{
    fittingSpot(const QPair<int, int>& c1, const QPair<int, int> &c2,const int num)
        : firstTile(c1), secondtTile(c2), rotation(num)
    {

    }

    QPair<int, int> firstTile;
    QPair<int, int> secondtTile;
    int rotation;
}FitPlace;


class Simulator
{
public:

    Simulator(SetOfAssemblyTiles *S, QMap<int, int> &StrengthFunction, int Theta, int StepNumber, QMap<int, QColor> &C);
    /*
     Post-Condition: Simulator with initial set of tiles S, strength map, theta parameter, and # of steps is created
     */
    void initialize();
    /*
     Post-Condition: All initialization goes here
     */
    void startSimulation();
    /*
     Main function that starts simulation
     */

    QList<DisplayTile *> toDisplayTile(AssemblyTile * T);
    //Converts Assembly tile into Display tile, returns it as a list of display tiles

    QList<SetOfAssemblyTiles *> &getAssemblies();
    //Get the list of all sets of assembly tiles

private:
   // SetOfAssemblyTiles & createNewSetOfAssemblyTiles();
    /*
     Post-Condition: New empty set of assembly tiles is created and returned
     */
    SetOfAssemblyTiles & selectMostCurrentSetOfAssemblyTiles();
    /*
     Post-Condition: Most updated set of assembly tiles is returned. This set contains tiles that will be picked as First Assembly Tiles
     */
    QList<FitPlace*> *findFittingSpots(AssemblyTile &T1,AssemblyTile &T2);
    /*
     Post-Condition: All possible fitting places of T1 and T2 are found and put in a list
     */
    AssemblyTile * attemptToCombine(AssemblyTile *T1, AssemblyTile *T2, FitPlace *place);
    /*
     Post-Condition: T1 and T2 are attempted to be combined at places first and second. If successful, pointer to a new tile is returned.
     If not successful, NULL is returned
     */

    bool checkOverlapAndStrength(AssemblyTile & T1, AssemblyTile & T2, QList<boundaryPoint *> *boundary);
    /*
     Post-Condition: Check if T1 and T2 contain an overlap of xy coordinates, i.e. do not fit each other.
     return true, if there is an overlap, and false otherwise. Also construct a list of boundary points, and check bond strength
     */
    int getBondStrength(ActiveTile &t1, ActiveTile &t2, direction boundary);
    /*
     Post-Condition: returns the highest bond strenghth of tile t1 and t2 at specified direction of tile t1
     */
    void tileModificationFunction(AssemblyTile & T, QList<boundaryPoint *> *boundary);
    /*
     Post-Condition: Apply tile modification function to tile T, also make boundary list empty at the end
     */


    //Attributes go next
    int currentStep;
    AssemblyTileSetManager manager;
    QMap<int, int> StrengthMap;
    int ThetaParameter;
    int NumberOfSteps;
    QMap<int, QColor> ColorMap;

    /*//Not sure about variables below yet
    int SetOfAssemblyTilesIterator;
    int FirstAssemblyTileIterator;
    int SecondAssemblyTileIterator;*/
};

#endif  //_SIMULATOR_H
