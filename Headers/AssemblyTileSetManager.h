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
    SetOfAssemblyTiles & createANewSet();
    /*
     Post-Condition: An empty set is added to the collection of sets, and the reference to this set is returned
     */
    QList<SetOfAssemblyTiles> & getListOfSets();
    /*
     Post-Condition: List of assembly tile sets is returned
     */
    void DeleteSet(SetOfAssemblyTiles & S);
    /*
     Post-Condition: If set S is in the collection, it is deleted
     */
    void StoreSetOnHardrive(int index);
    /*
     Post-Condition: Set that corresponds to index is stored on the hardrive
     */
    void LoadSetFromHardrive(int index);
    /*
     Post-Condition: Set that corresponds to index is retrived from the hardrive
     */
private:
    QList<SetOfAssemblyTiles> ListOfAssemblyTileSets;
    int NumberOfSets;
};

#endif  //_ASSEMBLYTILESETMANAGER_H