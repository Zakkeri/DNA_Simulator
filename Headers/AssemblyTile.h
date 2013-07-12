//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : AssemblyTile.h
//  @ Date : 5/20/2013
//  @ Author : 
//
//


#ifndef _ASSEMBLYTILE_H
#define _ASSEMBLYTILE_H
#include<QPair>
#include<QList>
#include<QMap>
#include"ActiveTile.h"
#define DEBUG
//#include"../Headers/Simulator.h"
struct freeActiveLabel
{
    freeActiveLabel(int l, direction dir, QPair<int, int> xy)
        :label(l), side(dir), xyCoord(xy)
    {

    }

    bool match(const freeActiveLabel& l)const
    {
        return this->label + l.label == 0;
    }

    bool operator==(const freeActiveLabel other)
    {
        return (this->label == other.label) && (this->side == other.side) && (this->xyCoord == other.xyCoord);
    }

    int label;
    direction side;
    QPair<int, int> xyCoord;
};


// Needed to move this here because the compiler was complaining.
struct boundaryPoint
{
    boundaryPoint(const bool tile,const QPair<int, int> coord,const direction dir)
        : isT1(tile), x_y(coord), side(dir)
    {

    }
    bool isT1;  //to tell from which assembly tile the boundary point is infered
    QPair<int, int> x_y; //coordinates of tile1 on the boundary point
    direction side; //where the boundary is
};


class AssemblyTile
{
public:

#ifdef DEBUG
    static int ID;   //unique id for everytile
#endif
    AssemblyTile(ActiveTile *T);
    /*
     Constructor with one tile
     Post-Condition: Assembly tile object that consists of only one tile is created
     */
    AssemblyTile(AssemblyTile &T1, AssemblyTile &T2, QList<boundaryPoint *> *boundary);
    /*
     Constructor with for assembly tile
     Post-Condition: Assembly tile object is created from combination of two assembly tiles
     */

   AssemblyTile(AssemblyTile &T);
    /*
     Copy-constructor
     */

	~AssemblyTile();
    /*
     Default destructor
     */
    ActiveTile * getTileFromCoordinates(QPair<int, int> coordinate);
    /*
     Post-Condition: Reference to the ActiveTile that is placed on asked coordinate is returned
     */

    void moveAssemblyTile(QPair<int, int> shift);
    /*
     Post-Condition: Whole assembly tile is moved
     */
    void rotateAssemblyTile(QPair<int, int> refPoint, int times);
    /*
     Post-Condition: Assembly tile is rotated required amount of times along reference point
     */

    QList<ActiveTile *> &getListOfActiveTiles();
    /*
     Post-Condition: List of all active tiles is returned
     */

    void addTile(ActiveTile *newTile);
    /*
     Post-Condition: The tile is added to the list of active tiles and the tile count is increased
     */

    int getIndex();
    /*
     Post-Condition: Returns the index of a tile
     */

    void setIndex(int ind);
    /*
     Post-Condition: Sets the index of a tile
     */

    QMap<QPair<int, int>, ActiveTile *> &getMap();
    /*
     Map is returned
     */

    QList<freeActiveLabel> & getListOfFreeSides();
    /*
     Post-Conditions: listOfFreeSides is returned
     */

    bool operator==(const AssemblyTile & other)const;
    /*
     Overloaded equal operator
     */

    QPair<int, int> nominalToMap(QPair<int, int> coordinate) const;
    /*
     Takes a coordinate of the tile and changes it to the spot in the map
     */


private:
    QList<ActiveTile*> ListOfActiveTiles;
    int NumberOfActiveTiles;
    QPair<int, int> tileOffset;
    direction rotation;
    QMap<QPair<int, int>, ActiveTile*> map	;//will map coordinate to tile
    int index;  //in each set tiles will be numbered by index, so we can easily choose first and second tile from the same set
    QList<freeActiveLabel> listOfFreeSides; //will hold a set of all free sides of the whole Assembly tile
#ifdef DEBUG
    int uniqueID;   //unique id for everytile
#endif



};

#endif  //_ASSEMBLYTILE_H
