//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Simulator.cpp
//  @ Date : 5/20/2013
//  @ Author : 
//
//

#include <QDebug>
#include "../Headers/Simulator.h"

Simulator::Simulator(SetOfAssemblyTiles S, QMap<int, int> &StrengthFunction, int Theta, int StepNumber)
/*
 Post-Condition: Simulator with initial set of tiles S, strength map, theta parameter, and # of steps is created
 */
    : manager(S), StrengthMap(StrengthFunction), ThetaParameter(Theta), NumberOfSteps(StepNumber)
{

}

void Simulator::initialize()
/*
 Post-Condition: All initialization goes here
 */
{
    currentStep = 1;
}

void Simulator::startSimulation()
/*
 Main function that starts simulation
 */
{
    for(currentStep; currentStep <= NumberOfSteps; currentStep++)   //Perform simulation, until the number of required steps is reached
    {
        SetOfAssemblyTiles newSet;  //New empty set of Assembly tiles
        SetOfAssemblyTiles currentSet = selectMostCurrentSetOfAssemblyTiles();  //most up to date set of assembly tiles
        QList<AssemblyTile>::Iterator i;
        for(i = currentSet.getListOfAssemblyTiles().begin(); i!=currentSet.getListOfAssemblyTiles().end(); i++)
        {
            AssemblyTile t1 = *i;   //get next first assembly tile t1
            QList<SetOfAssemblyTiles>::Iterator j;
            for(j = manager.getListOfSets().begin(); j!=manager.getListOfSets().end(); j++)//iterate through every set of assembly tiles
            {
                SetOfAssemblyTiles temp = *j;   //get temporal set of assembly tiles for picking the second assembly tile
                QList<AssemblyTile>::Iterator k;
                for(k = temp.getListOfAssemblyTiles().begin(); k!=temp.getListOfAssemblyTiles().end(); k++)    //each tile in temp iterate through and try to combine two tiles
                {
                    AssemblyTile t2 = *k;  //chose second assembly tile
                    if(&temp == &currentSet && t2.getIndex() < t1.getIndex()) //check for redundant tiles
                    {
                        continue;
                    }
                    QList<FitPlace*> *spots;
                    spots = findFittingSpots(t1, t2);   //get all fitting spots
                    if(spots->isEmpty())   //check if there are any fitting spot
                    {
                        delete spots;   //free memory
                        continue;
                    }
                    QList<FitPlace*>::Iterator fit;
                    for(fit = spots->begin(); fit!=spots->end(); fit++)  //iterata through each fitting spot
                    {
                        FitPlace * next = *fit;   //get next spot
                        AssemblyTile* combined = attemptToCombine(t1, t2, next);
                        delete next;    //free the memory
                        if(combined == 0)   //check if tiles were combined
                        {
                            continue;
                        }

                        newSet.addAssemblyTile(*combined);
                    }

                    delete spots;   //free the memory
                }
            }

         }
        if(newSet.isEmpty())    //check if new set is empty
        {
            break;
        }
        manager.addSet(newSet);
    }

}

/*SetOfAssemblyTiles & Simulator::createNewSetOfAssemblyTiles()
/*
 Post-Condition: New empty set of assembly tiles is created and returned
 /
{

}*/
SetOfAssemblyTiles & Simulator::selectMostCurrentSetOfAssemblyTiles()
/*
 Post-Condition: Most updated set of assembly tiles is returned. This set contains tiles that will be picked as First Assembly Tiles
 */
{
    return manager.getAssemblyTileSet(currentStep - 1);
}

QList<FitPlace*> *Simulator::findFittingSpots(AssemblyTile &T1,AssemblyTile &T2)
/*
 Post-Condition: All possible fitting places of T1 and T2 are found and put in a list
 */
{
    QList<FitPlace*> *fitPlaces = new QList<FitPlace*>; //create a new list of fit places
    foreach(freeActiveLabel label1, T1.getListOfFreeSides())    //for each free side of T1
    {
        foreach(freeActiveLabel label2, T2.getListOfFreeSides())//find a matching label from T2
        {
            if(label1.match(label2))    //if two labels match, then create a new fitting spot
            {
                QPair<int, int> coord;
                switch(label1.side) //calculate first coordinate
                {
                    case x: coord.first = label1.xyCoord.first + 1;
                            coord.second = label1.xyCoord.second;
                            break;

                    case y: coord.first = label1.xyCoord.first;
                            coord.second = label1.xyCoord.second + 1;
                            break;

                    case _x: coord.first = label1.xyCoord.first - 1;
                             coord.second = label1.xyCoord.second;
                             break;

                    case _y: coord.first = label1.xyCoord.first;
                             coord.second = label1.xyCoord.second - 1;
                             break;

                }
                int rotation = (label1.side - ((label2.side + 2)%4)) % 4;   //calculate rotation
                FitPlace *match = new FitPlace(coord, label2.xyCoord, rotation);    //create FirPlace and append it to the list
                fitPlaces->append(match);
            }
        }
    }

    return fitPlaces;
}

AssemblyTile * Simulator::attemptToCombine(AssemblyTile T1,AssemblyTile T2, FitPlace *place)
/*
 Post-Condition: T1 and T2 are attempted to be combined at places first and second. If successful, pointer to a new tile is returned.
 If not successful, NULL is returned
 */
{
    T2.rotateAssemblyTile(place->secondtTile, place->rotation); //rotate second tile

    QPair<int, int> shift(place->firstTile.first - place->secondtTile.first, place->firstTile.second - place->secondtTile.second);
    T2.moveAssemblyTile(shift); //shift second tile

    QList<boundaryPoint*> boundaryList;
    if(checkOverlapAndStrength(T1, T2, &boundaryList)) //check if two tiles overlap and have enough bond strength
    {
        foreach(boundaryPoint* next, boundaryList)  //if not, free the memory and return 0
        {
            delete next;
        }

        return 0;
    }


    AssemblyTile *newTile = new AssemblyTile(T1, T2, &boundaryList);    //if yes, create a new tile

    tileModificationFunction(*newTile, &boundaryList);  //apply tile modificattion function

    if(!boundaryList.isEmpty())
    {
        qDebug()<<"Error!!!, List must be empty";
    }

    return newTile;
}

bool Simulator::checkOverlapAndStrength(AssemblyTile & T1, AssemblyTile & T2, QList<boundaryPoint*> *boundary)
/*
 Post-Condition: Check if T1 and T2 contain an overlap of xy coordinates, i.e. do not fit each other.
 return true, if there is an overlap, and false otherwise. Also construct a list of boundary points, and check bond strength
 */
{
    int strength = 0;
    if(T1.getListOfActiveTiles().length() > T2.getListOfActiveTiles().length()) //if T2 has less active tiles, then process it
    {
        foreach(ActiveTile t2, T2.getListOfActiveTiles())   //for each active tile in T2
        {
            ActiveTile *temp = T1.getTileFromCoordinates(t2.getCoordinates());  //check if there is an overlap
            if(temp != 0)   //if there is an overlap, then return true
            {
                return true;
            }


            for(int i = 0; i < 4; i++)  //otherwise, check if t2 is on the boundary
            {
                if(t2.getNeighbor((direction)i))    //if t2 has a neighbor in the i'th direction, then go to next side
                {
                    continue;
                }
                int x = t2.getCoordinates().first;
                int y = t2.getCoordinates().second;

                switch(i)   //otherwise check if there is any active tile from assembly tile T1, and if so add boundary point to the list
                {
                case 0: if(T1.getTileFromCoordinates(QPair<int, int>(x + 1, y)))
                    {
                        if(strength < this->ThetaParameter)
                        {
                            strength += getBondStrength(t2, *T1.getTileFromCoordinates(QPair<int, int>(x + 1, y)), (direction)i);
                        }
                        boundaryPoint * bound = new boundaryPoint(false, t2.getCoordinates(), (direction)0);
                        boundary->append(bound);

                    }
                         break;

                case 1: if(T1.getTileFromCoordinates(QPair<int, int>(x , y + 1)))
                    {
                        if(strength < this->ThetaParameter)
                        {
                            strength += getBondStrength(t2, *T1.getTileFromCoordinates(QPair<int, int>(x, y + 1)), (direction)i);
                        }
                        boundaryPoint * bound = new boundaryPoint(false, t2.getCoordinates(), (direction)1);
                        boundary->append(bound);
                    }
                     break;

                case 2: if(T1.getTileFromCoordinates(QPair<int, int>(x - 1, y)))
                    {
                        if(strength < this->ThetaParameter)
                        {
                            strength += getBondStrength(t2, *T1.getTileFromCoordinates(QPair<int, int>(x - 1, y)), (direction)i);
                        }
                        boundaryPoint * bound = new boundaryPoint(false, t2.getCoordinates(), (direction)2);
                        boundary->append(bound);
                    }
                     break;

                case 3: if(T1.getTileFromCoordinates(QPair<int, int>(x, y - 1)))
                    {
                        if(strength < this->ThetaParameter)
                        {
                            strength += getBondStrength(t2, *T1.getTileFromCoordinates(QPair<int, int>(x, y - 1)), (direction)i);
                        }
                        boundaryPoint * bound = new boundaryPoint(false, t2.getCoordinates(), (direction)3);
                        boundary->append(bound);
                    }
                     break;
                }
            }

        }

    }
    else
    {
        foreach(ActiveTile t1, T1.getListOfActiveTiles())   //else T1 has less active tiles, so process all active tiles of T1
        {
            ActiveTile *temp = T2.getTileFromCoordinates(t1.getCoordinates());  //check if there is an overlap
            if(temp != 0)   //if there is an overlap, then return 0
            {
                return true;
            }


            for(int i = 0; i < 4; i++)  //otherwise, check if t2 is on the boundary
            {
                if(t1.getNeighbor((direction)i))    //if t2 has a neighbor in the i'th direction, then go to next side
                {
                    continue;
                }
                int x = t1.getCoordinates().first;
                int y = t1.getCoordinates().second;

                switch(i)   //otherwise check if there is any active tile from assembly tile T1, and if so add boundary point to the list
                {
                case 0: if(T2.getTileFromCoordinates(QPair<int, int>(x + 1, y)))
                    {
                        if(strength < this->ThetaParameter)
                        {
                            strength += getBondStrength(t1, *T2.getTileFromCoordinates(QPair<int, int>(x + 1, y)), (direction)i);
                        }
                        boundaryPoint * bound = new boundaryPoint(true, t1.getCoordinates(), (direction)0);
                        boundary->append(bound);

                    }
                         break;

                case 1: if(T2.getTileFromCoordinates(QPair<int, int>(x , y + 1)))
                    {
                        if(strength < this->ThetaParameter)
                        {
                            strength += getBondStrength(t1, *T2.getTileFromCoordinates(QPair<int, int>(x, y + 1)), (direction)i);
                        }
                        boundaryPoint * bound = new boundaryPoint(true, t1.getCoordinates(), (direction)1);
                        boundary->append(bound);
                    }
                     break;

                case 2: if(T2.getTileFromCoordinates(QPair<int, int>(x - 1, y)))
                    {
                        if(strength < this->ThetaParameter)
                        {
                            strength += getBondStrength(t1, *T2.getTileFromCoordinates(QPair<int, int>(x - 1, y)), (direction)i);
                        }
                        boundaryPoint * bound = new boundaryPoint(true, t1.getCoordinates(), (direction)2);
                        boundary->append(bound);
                    }
                     break;

                case 3: if(T2.getTileFromCoordinates(QPair<int, int>(x, y - 1)))
                    {
                        if(strength < this->ThetaParameter)
                        {
                            strength += getBondStrength(t1, *T2.getTileFromCoordinates(QPair<int, int>(x, y - 1)), (direction)i);
                        }
                        boundaryPoint * bound = new boundaryPoint(true, t1.getCoordinates(), (direction)3);
                        boundary->append(bound);
                    }
                     break;
                }
            }

        }

    }

    if(strength < this->ThetaParameter)
    {
        return true;
    }

    return false;
}

bool Simulator::getBondStrength(ActiveTile & t1, ActiveTile & t2, direction boundary)
/*
 Post-Condition: returns the highest bond strenghth of tile t1 and t2 at specified direction of tile t1
 */
{
    int strength = 0;
    foreach(int label1, t1.getActiveLabels(boundary))
    {
        foreach(int label2, t2.getActiveLabels((direction)(boundary + 2)))
        {
            if(label1 + label2 == 0)
            {
                if(strength < abs(StrengthMap[label1]))
                {
                    strength = abs(StrengthMap[label1]);
                }
            }
        }
    }

    return strength;

}

void Simulator::tileModificationFunction(AssemblyTile & T, QList<boundaryPoint *> *boundary)
/*
 Post-Condition: Apply tile modification function to tile T, also make boundary list empty at the end
 */
{

}
