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

class ActiveTile;

class AssemblyTile
{
public:
	AssemblyTile(ActiveTile T);
	AssemblyTile(ActiveTile T1, ActiveTile T2);
	~AssemblyTile();
    int ListOfActiveTiles;
    int NumberOfActiveTiles;
	int map	//will map coordinate to tile
    void GetTileFromCoordinates();
    void MoveAssemblyTile();
    void RotateAssemblyTile();
};

#endif  //_ASSEMBLYTILE_H
