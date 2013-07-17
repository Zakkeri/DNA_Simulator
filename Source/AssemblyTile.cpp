//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : AssemblyTile.cpp
//  @ Date : 5/20/2013
//  @ Author : 
//
//


#include "../Headers/AssemblyTile.h"


#ifdef DEBUG
    int AssemblyTile::ID = 0;   //unique id for everytile
#endif
AssemblyTile::AssemblyTile(ActiveTile *T)
/*
 Constructor with one tile
 Post-Condition: Assembly tile object that consists of only one tile is created
 */
{
#ifdef DEBUG
    this->uniqueID = AssemblyTile::ID;
    AssemblyTile::ID++;
#endif

    T->setParent(this); //set tiles' neighboor
    T->setCoordinates(QPair<int, int>(0,0));
    ListOfActiveTiles << T;
    NumberOfActiveTiles = 1;


    tileOffset = QPair<int, int>(0,0);
    rotation = x;
    map[QPair<int, int>(0,0)] = ListOfActiveTiles.first();

    for(int dir = 0; dir < 4; dir++)
    {
        foreach(int label, T->getActiveLabels((direction)dir))
        {
            listOfFreeSides << freeActiveLabel(label, (direction) dir, T->getCoordinates());
        }
    }

    isCopy = false; //Workaround

}

AssemblyTile::AssemblyTile(AssemblyTile &T1, AssemblyTile &T2, QList<boundaryPoint *> *boundary)
/*
 Constructor with for assembly tile
 Post-Condition: Assembly tile object is created from combination of two assembly tiles
 */
{
#ifdef DEBUG
    this->uniqueID = AssemblyTile::ID;
    AssemblyTile::ID++;
#endif

    AssemblyTile *toAssembly;
    AssemblyTile *fromAssembly;

    // Tells which assembly tile is the on not getting moved, I'm assuming
    // all boundary points have the same value of isT1.
    if(boundary->value(0)->isT1)
    {
        toAssembly = &T1;
        fromAssembly = &T2;
    }else{
        fromAssembly = &T1;
        toAssembly = &T2;
    }

    // Initilize is to be like the one the tiles are moving to
    this->ListOfActiveTiles = toAssembly->ListOfActiveTiles;
    this->listOfFreeSides = toAssembly->listOfFreeSides;
    this->map = toAssembly->map;
    this->NumberOfActiveTiles = toAssembly->NumberOfActiveTiles;
    this->rotation = toAssembly->rotation;
    this->tileOffset = toAssembly->tileOffset;

    // Add in the list of free sides from the second tile
    this->listOfFreeSides << fromAssembly->listOfFreeSides;

    // Add the tiles fromt the second assembly tile
    for(QList<ActiveTile*>::iterator next = fromAssembly->getListOfActiveTiles().begin(); next != fromAssembly->getListOfActiveTiles().end(); ++next)
    {
        this->map.insert(this->nominalToMap((*next)->getCoordinates()), *next);
        this->addTile(*next);
    }

    // Add new neighbors
    foreach(boundaryPoint *next, *boundary)
    {
        ActiveTile *firstTile = this->getTileFromCoordinates(next->x_y);
        ActiveTile *otherTile;

        //Determine which tile is on the other side of the boundary
        switch(next->side)
        {
        case x:
            otherTile = this->getTileFromCoordinates(QPair<int, int>(next->x_y.first + 1, next->x_y.second));
            break;
        case y:
            otherTile = this->getTileFromCoordinates(QPair<int, int>(next->x_y.first, next->x_y.second + 1));
            break;
        case _x:
            otherTile = this->getTileFromCoordinates(QPair<int, int>(next->x_y.first - 1, next->x_y.second));
            break;
        case _y:
            otherTile = this->getTileFromCoordinates(QPair<int, int>(next->x_y.first, next->x_y.second - 1));
            break;
        }

        // Set the neighbors
        firstTile->setNeighbor(next->side,otherTile);
        otherTile->setNeighbor((direction)((next->side + 2)%4), firstTile);

        // Remove the boundary
        foreach(freeActiveLabel nextLabel, this->getListOfFreeSides())
        {
            if((nextLabel.xyCoord == firstTile->getCoordinates() && nextLabel.side == next->side) ||
                    (nextLabel.xyCoord == otherTile->getCoordinates() && nextLabel.side == (direction)((next->side + 2)%4)))
            {
                this->listOfFreeSides.removeOne(nextLabel);
            }
        }
    }

    this->isCopy = false;   //Workaround
}

AssemblyTile::AssemblyTile(const AssemblyTile &T)
/*
 Copy-constructor
 */
{
#ifdef DEBUG
    this->uniqueID = AssemblyTile::ID;
    AssemblyTile::ID++;
#endif

    this->index = T.index;
    this->listOfFreeSides = T.listOfFreeSides;
    this->NumberOfActiveTiles = T.NumberOfActiveTiles;
    this->rotation = T.rotation;
    this->tileOffset = T.tileOffset;

    //iterate through the list of ActiveTiles and add tiles to the list and map
    for(QList<ActiveTile*>::const_iterator it = T.ListOfActiveTiles.begin(); it != T.ListOfActiveTiles.end(); ++it)
    {
        ActiveTile &next = **it;
        ActiveTile * addTile = new ActiveTile(next);
        this->ListOfActiveTiles<< addTile;
        this->map[next.getCoordinates()] = addTile;
        addTile->setParent(this);
    }

    //iterate second time to assign neighbors
    for(QList<ActiveTile*>::const_iterator it = T.ListOfActiveTiles.begin(); it != T.ListOfActiveTiles.end(); ++it)
    {
        ActiveTile &next = **it;    //get tile
        ActiveTile &correspondingTile = *(this->map[next.getCoordinates()]);    //get corresponding tile
        for(int i = 0; i < 4; i++)  //set all 4 neighbors
        {
            ActiveTile * neigh = next.getNeighbor((direction)i);
            if(neigh == NULL)
            {
                continue;
            }
            correspondingTile.setNeighbor((direction)i, this->map[neigh->getCoordinates()]);
        }

    }

    this->isCopy = true; //Workaround
}

AssemblyTile::~AssemblyTile()
/*
 Default destructor
 */
{
    if(!isCopy) //if it not a copy, then delete tiles
    {
        //Delete each ActiveTile from the list
        for(QList<ActiveTile*>::iterator tile = this->ListOfActiveTiles.begin(); tile != this->ListOfActiveTiles.end(); ++tile)
        {
            delete *tile;
        }
    }

}

ActiveTile *AssemblyTile::getTileFromCoordinates(QPair<int, int> coordinate)
/*
 Post-Condition: Reference to the ActiveTile that is placed on asked coordinate is returned
 */
{
    if(map.contains(this->nominalToMap(coordinate)))
    {
        return map[this->nominalToMap(coordinate)];
    }
    else
    {
        return NULL;
    }
}

void AssemblyTile::moveAssemblyTile(QPair<int, int> shift)
/*
 Post-Condition: Whole assembly tile is moved
 */
{
    //ActiveTile currentTile;
    QList<ActiveTile*>::Iterator i;
    for(i = ListOfActiveTiles.begin(); i != ListOfActiveTiles.end(); i++)
    {
        (*i)->moveTile(shift);
    }

    this->tileOffset.first -= shift.first;
    this->tileOffset.second -= shift.second;
}

void AssemblyTile::rotateAssemblyTile(QPair<int, int> refPoint, int times)
/*
 Post-Condition: Assembly tile is rotated required amount of times along reference point
 */
{
    // First, move the refPoint to (0,0)
    this->moveAssemblyTile(QPair<int,int>(-refPoint.first, -refPoint.second));

    // Then, rotate the assembly tile around (0,0)
    switch(times % 4)
    {
    case 0:
        break;
    case 1:
        // For counter-clockwise rotation, x->y, y->-x
        this->tileOffset = QPair<int, int>(-this->tileOffset.second, this->tileOffset.first);
        this->rotation = (direction)((this->rotation + 1)%4);
        break;
    case 2:
        // For 180 degree rotation, x->-x, y->-y
        this->tileOffset = QPair<int, int>(-this->tileOffset.first, -this->tileOffset.second);
        this->rotation = (direction)((this->rotation + 2)%4);
        break;
    case 3:
        // For clockwise rotation, x->-y, y->x
        this->tileOffset = QPair<int, int>(this->tileOffset.second, -this->tileOffset.first);
        this->rotation = (direction)((this->rotation + 3)%4);
        break;
    }

    // Then, move the refPoint back to where it should be
    this->moveAssemblyTile(refPoint);
}

QList<ActiveTile*> & AssemblyTile::getListOfActiveTiles()
/*
 Post-Condition: List of all active tiles is returned
 */
{
    return this->ListOfActiveTiles;
}

int AssemblyTile::getIndex()
/*
 Post-Condition: Returns the index of a tile
 */
{
    return index;
}

void AssemblyTile::setIndex(int ind)
/*
 Post-Condition: Sets the index of a tile
 */
{
    index = ind;
}

QMap<QPair<int, int>, ActiveTile*> & AssemblyTile::getMap()
/*
 Map is returned
 */
{
    return this->map;
}
QList<freeActiveLabel> &AssemblyTile::getListOfFreeSides()
/*
 Post-Conditions: listOfFreeSides is returned
 */
{
    return this->listOfFreeSides;
}

bool AssemblyTile::operator==(const AssemblyTile & other)const
/*
 Overloaded equal operator
 */
{
    // Check to see if they have the same number of tiles
    if(other.NumberOfActiveTiles != this->NumberOfActiveTiles) return false;

    AssemblyTile otherTile = other;
    bool matching = true;
    QList<QPair<int, int> > tileCoords, otherCoords;
    QPair<int, int> shift;

    // Extract the list of keys from either, please note that these are
    // automatically in ascending order, with the lowest tiles being the
    // ones furthest to the left, then furthest down.
    tileCoords = this->map.keys();
    otherCoords = otherTile.map.keys();

    // Need to check if the two lists are the same for all four rotations
    for(int i = 0; i < 4; i++)
    {
        // First, figure out how much the offset is, then account for it.
        shift = QPair<int, int>(tileCoords[0].first - otherCoords[0].first, tileCoords[0].second - otherCoords[0].second);

        // See if the lists match
        for(int j = 0; j < tileCoords.length(); j++)
        {
            //check if coordinate are equal
            if(tileCoords[j] != QPair<int, int>(otherCoords[j].first + shift.first, otherCoords[j].second + shift.second))

            {
                matching = false;
                break;
            }

            //if coordinates are equal, then check if tiles are equal
            ActiveTile *tile1 = this->map[this->nominalToMap(tileCoords[j])];
            ActiveTile *tile2 = otherTile.map[otherTile.nominalToMap(tileCoords[j])];
            if(!(*tile1 == *tile2))
            {
                matching = false;
                break;
            }
        }

        // If they don't match, rotate the other tile, resort the list and try again
        if(!matching)
        {
            for(QList<QPair<int, int> >::iterator currentPair = otherCoords.begin(); currentPair != otherCoords.end(); currentPair++)
            {
                *currentPair = QPair<int, int>(-currentPair->second, currentPair->first);
            }
            otherTile.rotateAssemblyTile(QPair<int,int>(0,0),1);
            qSort(otherCoords);
        }else{
            return true;
        }
    }

    return false;
}

QPair<int, int> AssemblyTile::nominalToMap(QPair<int, int> coordinate)const
{

    QPair<int, int> modifiedCoordinate;

    // To get the coordinate a tile is within the map, you'll have to take
    // it's current xy coordinate, undo the rotation, then undo the shift.
    switch(this->rotation)
    {
    case y:
        modifiedCoordinate = QPair<int, int>(coordinate.second, -coordinate.first);
        break;
    case _x:
        modifiedCoordinate = QPair<int, int>(-coordinate.first, -coordinate.second);
        break;
    case _y:
        modifiedCoordinate = QPair<int, int>(-coordinate.second, coordinate.first);
        break;
    default:
        modifiedCoordinate = coordinate;
        break;
    }
    //Changed minus to plus!!!
    modifiedCoordinate.first += this->tileOffset.first;
    modifiedCoordinate.second += this->tileOffset.second;
    return modifiedCoordinate;
}

void AssemblyTile::addTile(ActiveTile *newTile)
{
    this->ListOfActiveTiles.append(newTile);
    this->NumberOfActiveTiles++;
}

