//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : AssemblyTileSetManager.h
//  @ Date : 5/20/2013
//  @ Author : 
//
//


#ifndef _ASSEMBLYTILESETMANAGER_H
#define _ASSEMBLYTILESETMANAGER_H
#include"SetOfAssemblyTiles.h"
#include<QList>

class AssemblyTileSetManager
{
public:
	AssemblyTileSetManager();
    /*
     Default constructor
     */
    AssemblyTileSetManager(SetOfAssemblyTiles &S);
    /*
     Post-Condition: Assembly tile set manager is created and contains one set of assembly tiles
     */
	~AssemblyTileSetManager();
    /*
     Default destructor
     */

    SetOfAssemblyTiles & getAssemblyTileSet(int index);
    /*
     Post-Condition: Set that corresponds to index is returned
     */
    void addSet(SetOfAssemblyTiles &newSet);
    /*
     Post-Condition: A new set is added to the collection of sets
     */
    QList<SetOfAssemblyTiles> & getListOfSets();
    /*
     Post-Condition: List of assembly tile sets is returned
     */
    void deleteSet(SetOfAssemblyTiles &S);
    /*
     Post-Condition: If set S is in the collection, it is deleted
     */
    void storeSetOnHardrive(int index)const;
    /*
     Post-Condition: Set that corresponds to index is stored on the hardrive
     */
    void loadSetFromHardrive(int index) const;
    /*
     Post-Condition: Set that corresponds to index is retrived from the hardrive
     */
private:
    QList<SetOfAssemblyTiles> listOfAssemblyTileSets;
    int numberOfSets;
};

#endif  //_ASSEMBLYTILESETMANAGER_H
