//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : SetOfAssemblyTiles.h
//  @ Date : 5/20/2013
//  @ Author : 
//
//


#ifndef _SETOFASSEMBLYTILES_H
#define _SETOFASSEMBLYTILES_H
#include"../Headers/AssemblyTile.h"
#include<QList>

//#define DEBUG

class SetOfAssemblyTiles
{
public:

#ifdef DEBUG
    static int ID;   //unique id for everytile
#endif

	SetOfAssemblyTiles();
    /*
     Default Constructor
     */
    SetOfAssemblyTiles(AssemblyTile *A);
    /*
     Post-Condition: Set of assembly Tiles is created with one assembly tile in it
     */
    SetOfAssemblyTiles(AssemblyTile *A [], int n);
    /*
     Post-Condition: Set of assembly Tiles is created with n assembly tiles in it
     */
	~SetOfAssemblyTiles();
    /*
     Default destructor
     */

    void addAssemblyTile(AssemblyTile * const T);
    /*
     Post-Condition: If assembly tile is not in the set, then it is added to the set
     */
    void removeAssemblyTile(AssemblyTile * const T);
    /*
     Post-Condition: If assembly tile is in the set, then it is removed from the set
     */

    bool checkIfTileIsInTheSet(const AssemblyTile * const T) const;
    /*
     Post-Condition: If T is in the set, then function returns true, and false otherwise
     */

    AssemblyTile & getAssemblyTile(int index);
    /*
     Post-Condition: Return an assembly tile corresponding to the index
     */
    QList<AssemblyTile*> & getListOfAssemblyTiles();
    /*
     Post-Condition: Returns list of all assembly tiles
     */
    int getSetId()const;
    /*
     Post-Condition: Returns the id of current set, which corresponds to the step numberOfAssemblyTiles
     */

    void setID(int ind);
    /*
     Post-Condition: Sets the id of current set, which corresponds to the step numberOfAssemblyTiles
     */
    bool isEmpty() const;
    /*
     Post-Condition: If set is empty, returns true, and false otherwise
     */

    bool operator==(const SetOfAssemblyTiles& other)const;
    /*
     Overloaded equal operator
     */

    bool contains(const AssemblyTile * const T)const;
    /*
     Post-Condition: returns true if set already has tile T, and false otherwise
     */

private:

    QList<AssemblyTile*> listOfAssemblyTiles;
    int numberOfAssemblyTiles;
    int setID_StepNumber;

#ifdef DEBUG
    int uniqueID;
#endif

};


#endif  //_SETOFASSEMBLYTILES_H
