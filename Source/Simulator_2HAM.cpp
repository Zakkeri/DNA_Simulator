
#include <QQueue>
#include <QDebug>
#include "../Headers/Simulator_2HAM.h"

Simulator_2HAM::Simulator_2HAM(SetOfAssemblyTiles *S, QMap<int, int> &StrengthFunction, int Theta, int StepNumber, QMap<int, QColor> &C)

/*
 Post-Condition: Simulator_2HAM with initial set of tiles S, strength map, theta parameter, and # of steps is created
 */
    : manager(S), StrengthMap(StrengthFunction), ThetaParameter(Theta), NumberOfSteps(StepNumber), ColorMap(C)

{
#ifdef DEBUG
    qDebug()<<"Constructing Simulator_2HAM object";
#endif
}

void Simulator_2HAM::initialize()
/*
 Post-Condition: All initialization goes here
 */
{
#ifdef DEBUG
    qDebug()<<"Initializing constructor";
#endif
    currentStep = 1;
}

void Simulator_2HAM::startSimulation()
/*
 Main function that starts simulation
 */
{
#ifdef DEBUG
    qDebug()<<"Simulation for "<<NumberOfSteps<<" steps was started";
#endif
    for(; currentStep <= NumberOfSteps; currentStep++)   //Perform simulation, until the number of required steps is reached
    {
#ifdef DEBUG
    qDebug()<<"\n\nBeginig step #"<<currentStep;
#endif
        SetOfAssemblyTiles *newSet = new SetOfAssemblyTiles;  //New empty set of Assembly tiles
#ifdef DEBUG
    qDebug()<<"New set of tiles was created";
#endif
        SetOfAssemblyTiles &currentSet = selectMostCurrentSetOfAssemblyTiles();  //most up to date set of assembly tiles
#ifdef DEBUG
    qDebug()<<"Current set was selected";
#endif
        QList<AssemblyTile*>::Iterator i;
        for(i = currentSet.getListOfAssemblyTiles().begin(); i!=currentSet.getListOfAssemblyTiles().end(); i++)
        {
            AssemblyTile &t1 = **i;   //get next first assembly tile t1

#ifdef DEBUG

            qDebug()<<"Assembly tile "<<t1.getIndex()<<" was selected as first tile";
#endif
            QList<SetOfAssemblyTiles*>::Iterator j;
            for(j = manager.getListOfSets().begin(); j!=manager.getListOfSets().end(); ++j)//iterate through every set of assembly tiles
            {
                SetOfAssemblyTiles &temp = **j;   //get temporal set of assembly tiles for picking the second assembly tile
#ifdef DEBUG
                    qDebug()<<"Set "<<temp.getSetId()<<" was selected to iterate through";
#endif
                QList<AssemblyTile*>::Iterator k;
                for(k = temp.getListOfAssemblyTiles().begin(); k!=temp.getListOfAssemblyTiles().end(); k++)    //each tile in temp iterate through and try to combine two tiles
                {
                    AssemblyTile &t2 = **k;  //chose second assembly tile
#ifdef DEBUG
                    qDebug()<<"Second assembly tile "<<t2.getIndex()<<" was selected";
#endif
                    if(temp.getSetId() == currentSet.getSetId() && t2.getIndex() < t1.getIndex()) //check for redundant tiles
                    {
#ifdef DEBUG
    qDebug()<<"This tile is redundant one";
#endif
                        continue;
                    }

                    QList<FitPlace*> *spots;
#ifdef DEBUG
    qDebug()<<"Attempting to find fitting spots";
#endif
                    spots = findFittingSpots(t1, t2);   //get all fitting spots
                    if(spots->isEmpty())   //check if there are any fitting spot
                    {
#ifdef DEBUG
    qDebug()<<"No fitting spot was found";
#endif
                        delete spots;   //free memory
                        continue;
                    }
                    QList<FitPlace*>::Iterator fit;
#ifdef DEBUG
    qDebug()<<"Starting iteration through fitting spots";
#endif
                    for(fit = spots->begin(); fit!=spots->end(); fit++)  //iterata through each fitting spot
                    {
                        FitPlace * next = *fit;   //get next spot
#ifdef DEBUG
    qDebug()<<"Attempting to combine two tiles";
#endif
                        AssemblyTile* combined = attemptToCombine(&t1, &t2, next);
                        delete next;    //free the memory
                        if(combined == 0)   //check if tiles were combined
                        {
#ifdef DEBUG
    qDebug()<<"Failed to combine";
#endif
                            continue;
                        }
#ifdef DEBUG
    qDebug()<<"Tiles were combined succesfuly, pushing it into a set of new tiles";
#endif
                        if(!this->manager.isTileAdded(combined))
                        {
                            newSet->addAssemblyTile(combined);
                        }
                    }

                    delete spots;   //free the memory
                }
            }

         }
        if(newSet->isEmpty())    //check if new set is empty
        {
#ifdef DEBUG
            qDebug()<<"No new tiles were created, exiting simulation at step "<<currentStep;
#endif
            delete newSet;
            break;
        }
#ifdef DEBUG
    qDebug()<<"Adding new set to the manager";
#endif
        manager.addSet(newSet);
    }

    qDebug()<<"Simulation is over!";
#ifdef DEBUG
    qDebug()<<"Outputing result:\n\n";
    for(QList<SetOfAssemblyTiles*>::iterator iter1 = manager.getListOfSets().begin(); iter1 != manager.getListOfSets().end(); ++iter1)
    {
        SetOfAssemblyTiles &S = **iter1;
        qDebug()<<"Results for set "<<S.getSetId()<<"\n";
        for(QList<AssemblyTile*>::iterator iter2 = S.getListOfAssemblyTiles().begin(); iter2 != S.getListOfAssemblyTiles().end(); ++iter2)
        {
            AssemblyTile &T = **iter2;
            qDebug()<<"AssemblyTile "<<T.getIndex()<<"\n";
            for(QMap<QPair<int, int>, ActiveTile*>::iterator iter3 = T.getMap().begin(); iter3 != T.getMap().end(); ++iter3)
            {
                const QPair<int, int> & p = iter3.key();
                ActiveTile *t = T.getMap()[p];
                qDebug()<<"Active tile "<<t->getId()<<" Coordinate "<<t->getCoordinates().first<<" "<<t->getCoordinates().second;
                for(int side = 0; side < 4; side++)
                {
                    qDebug()<<"Side "<<side;
                    qDebug()<<"Active Labels:";
                    foreach(int label, t->getActiveLabels((direction)side))
                    {
                        qDebug()<<label;
                    }
                    qDebug()<<"Inactive Labels:";
                    foreach(int label, t->getInactiveLabels((direction)side))
                    {
                        qDebug()<<label;
                    }
                    qDebug()<<"Activation signals coming from this side:";
                    foreach(Signal sig, t->getActivationSignals((direction)side))
                    {
                        qDebug()<<"Label - "<<sig.label<<" Target Side - "<<sig.Target;
                    }
                    qDebug()<<"Transmission signals coming from this side:";
                    foreach(Signal sig, t->getTransmissionSignals((direction)side))
                    {
                        qDebug()<<"Label - "<<sig.label<<" Target Side - "<<sig.Target;
                    }

                    ActiveTile* neigh = t->getNeighbor((direction) side);
                    if(neigh == 0)
                    {
                        qDebug()<<"No neighbor on this side:";
                    }
                    else
                    {
                        qDebug()<<"Neighbor tile on this side: "<<neigh->getId();
                    }

                }
                qDebug()<<"Initiation Signals:";
                foreach(Signal sig, t->getInitiationSignals())
                {
                    qDebug()<<"Label - "<<sig.label<<" Target Side - "<<sig.Target;
                }

            }
            qDebug()<<"\n---------------------------------------------------------------------------------------\n";
        }
        qDebug()<<"\n-------------------------------------------------------------------------------------------\n\n";
    }

#endif

}

/*SetOfAssemblyTiles & Simulator_2HAM::createNewSetOfAssemblyTiles()

 Post-Condition: New empty set of assembly tiles is created and returned
 /
{

}*/
SetOfAssemblyTiles & Simulator_2HAM::selectMostCurrentSetOfAssemblyTiles()
/*
 Post-Condition: Most updated set of assembly tiles is returned. This set contains tiles that will be picked as First Assembly Tiles
 */
{
    return manager.getAssemblyTileSet(currentStep - 1);
}

QList<FitPlace*> *Simulator_2HAM::findFittingSpots(AssemblyTile &T1,AssemblyTile &T2)
/*
 Post-Condition: All possible fitting places of T1 and T2 are found and put in a list
 */
{
#ifdef DEBUG
    qDebug()<<"-------------------------------------------------------------------------------------------------";
    qDebug()<<"Inside findFittingSpots function";
#endif
    QList<FitPlace*> *fitPlaces = new QList<FitPlace*>; //create a new list of fit places
#ifdef DEBUG
    qDebug()<<"New list of fit places was initialized, starting iteration loop";
#endif
    foreach(freeActiveLabel label1, T1.getListOfFreeSides())    //for each free side of T1
    {
        foreach(freeActiveLabel label2, T2.getListOfFreeSides())//find a matching label from T2
        {
            if(label1.match(label2))    //if two labels match, then create a new fitting spot
            {
#ifdef DEBUG
                qDebug()<<"Found two matching labels: "<<label1.label<<" and "<<label2.label;
#endif
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
                if(rotation < 0) rotation = 4 + rotation; //if rotation is negative, bring it to positive integer
                FitPlace *match = new FitPlace(coord, label2.xyCoord, rotation);    //create FirPlace and append it to the list
                fitPlaces->append(match);
#ifdef DEBUG
                qDebug()<<"New fit place was created: \ncoordinate of the first tile - "<<match->firstTile.first<<" "<<match->firstTile.second<<
                          "\ncoordinate of the second tile - "<<match->secondtTile.first<<" "<<match->secondtTile.second<<
                          "\nrotation - "<<match->rotation;
#endif
            }
        }
    }
#ifdef DEBUG
    qDebug()<<"-------------------------------------------------------------------------------------------------";
#endif
    return fitPlaces;
}

AssemblyTile * Simulator_2HAM::attemptToCombine(AssemblyTile *T1,AssemblyTile *T2, FitPlace *place)
/*
 Post-Condition: T1 and T2 are attempted to be combined at places first and second. If successful, pointer to a new tile is returned.
 If not successful, NULL is returned
 */
{
#ifdef DEBUG
    qDebug()<<"-------------------------------------------------------------------------------------------------";
    qDebug()<<"Inside attemptToCombine function";
#endif
    if(T1 == T2)    //if passing the same tile for T1 and T2
    {
        T2 = new AssemblyTile(*T1);
    }
#ifdef DEBUG
    qDebug()<<"Rotating Assembly Tile "<<T2->getIndex();
#endif
    T2->rotateAssemblyTile(place->secondtTile, place->rotation); //rotate second tile
    //calculate the shift and unshift
    QPair<int, int> shift(place->firstTile.first - place->secondtTile.first, place->firstTile.second - place->secondtTile.second);
    QPair<int, int> unshift(place->secondtTile.first - place->firstTile.first, place->secondtTile.second - place->firstTile.second);
    //calculate unrotation
    int unrotation = 4 - place->rotation;
#ifdef DEBUG
    qDebug()<<"Shifting Assembly Tile "<<T2->getIndex();
#endif
    T2->moveAssemblyTile(shift); //shift second tile
#ifdef DEBUG
    qDebug()<<"Checking if tiles overlap or have the right bond strength";
#endif
    QList<boundaryPoint*> boundaryList;
    if(checkOverlapAndStrength(*T1, *T2, &boundaryList)) //check if two tiles overlap and have enough bond strength
    {
#ifdef DEBUG
    qDebug()<<"Tiles can't be combined";
#endif
        foreach(boundaryPoint* next, boundaryList)  //if not, free the memory and return 0
        {
            delete next;
        }
        if(T2->getIsCopy())
        {
            delete T2;
        }
        else//unshift and unrotate second tile
        {
            T2->moveAssemblyTile(unshift);
            T2->rotateAssemblyTile(place->secondtTile, unrotation);
        }
        return 0;
    }

#ifdef DEBUG
    qDebug()<<"Creating new combined Assembly Tile";
#endif
    AssemblyTile *newTile = new AssemblyTile(*T1, *T2, &boundaryList);    //if yes, create a new tile
#ifdef DEBUG
    qDebug()<<"Applying tile modification function";
#endif
    tileModificationFunction(*newTile, &boundaryList);  //apply tile modificattion function

    if(!boundaryList.isEmpty())
    {
        qDebug()<<"Error!!! List must be empty";
    }
#ifdef DEBUG
    qDebug()<<"-------------------------------------------------------------------------------------------------";
#endif
    if(T2->getIsCopy())
    {
        delete T2;
    }
    else //unshift and unrotate second tile
    {
        T2->moveAssemblyTile(unshift);
        T2->rotateAssemblyTile(place->secondtTile, unrotation);
    }
    return newTile;
}

bool Simulator_2HAM::checkOverlapAndStrength(AssemblyTile & T1, AssemblyTile & T2, QList<boundaryPoint*> *boundary)
/*
 Post-Condition: Check if T1 and T2 contain an overlap of xy coordinates, i.e. do not fit each other.
 return true, if there is an overlap, and false otherwise. Also construct a list of boundary points, and check bond strength
 */
{
#ifdef DEBUG
    qDebug()<<"-------------------------------------------------------------------------------------------------";
    qDebug()<<"Inside checkOverlapAndStrength function";
#endif
    int strength = 0;
    if(T1.getListOfActiveTiles().length() > T2.getListOfActiveTiles().length()) //if T2 has less active tiles, then process it
    {
#ifdef DEBUG
    qDebug()<<"Going to iterate through Assembly Tile "<<T2.getIndex();
#endif
    for(QList<ActiveTile*>::iterator iter_t2 = T2.getListOfActiveTiles().begin(); iter_t2 != T2.getListOfActiveTiles().end(); ++iter_t2)   //for each active tile in T2
        {
            ActiveTile & t2 = **iter_t2;
            ActiveTile *temp = T1.getTileFromCoordinates(t2.getCoordinates());  //check if there is an overlap
            if(temp != 0)   //if there is an overlap, then return true
            {
#ifdef DEBUG
    qDebug()<<"Assembly Tiles overlap, can't combine";
#endif
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
#ifdef DEBUG
                        qDebug()<<"Boundary point was added:\nTile coordinate - "<<bound->x_y.first<<" "<<bound->x_y.second<<
                                  "\nSide - "<<(int)bound->side;
#endif

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
#ifdef DEBUG
                        qDebug()<<"Boundary point was added:\nTile coordinate - "<<bound->x_y.first<<" "<<bound->x_y.second<<
                                  "\nSide - "<<(int)bound->side;
#endif
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
#ifdef DEBUG
                        qDebug()<<"Boundary point was added:\nTile coordinate - "<<bound->x_y.first<<" "<<bound->x_y.second<<
                                  "\nSide - "<<(int)bound->side;
#endif
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
#ifdef DEBUG
                        qDebug()<<"Boundary point was added:\nTile coordinate - "<<bound->x_y.first<<" "<<bound->x_y.second<<
                                  "\nSide - "<<(int)bound->side;
#endif
                    }
                     break;
                }
            }

        }

    }
    else
    {
        for(QList<ActiveTile*>::iterator activeTileIterator = T1.getListOfActiveTiles().begin();
            activeTileIterator != T1.getListOfActiveTiles().end(); activeTileIterator++)   //else T1 has less active tiles, so process all active tiles of T1
        {
            ActiveTile &t1 = **activeTileIterator;
#ifdef DEBUG
    qDebug()<<"Going to iterate through Assembly Tile "<<T1.getIndex();
#endif
            ActiveTile *temp = T2.getTileFromCoordinates(t1.getCoordinates());  //check if there is an overlap
            if(temp != 0)   //if there is an overlap, then return 0
            {
#ifdef DEBUG
    qDebug()<<"Assembly Tiles overlap, can't combine";
#endif
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
#ifdef DEBUG
                        qDebug()<<"Boundary point was added:\nTile coordinate - "<<bound->x_y.first<<" "<<bound->x_y.second<<
                                  "\nSide - "<<(int)bound->side;
#endif

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
#ifdef DEBUG
                        qDebug()<<"Boundary point was added:\nTile coordinate - "<<bound->x_y.first<<" "<<bound->x_y.second<<
                                  "\nSide - "<<(int)bound->side;
#endif
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
#ifdef DEBUG
                        qDebug()<<"Boundary point was added:\nTile coordinate - "<<bound->x_y.first<<" "<<bound->x_y.second<<
                                  "\nSide - "<<(int)bound->side;
#endif
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
#ifdef DEBUG
                        qDebug()<<"Boundary point was added:\nTile coordinate - "<<bound->x_y.first<<" "<<bound->x_y.second<<
                                  "\nSide - "<<(int)bound->side;
#endif
                    }
                     break;
                }
            }

        }

    }

    if(strength < this->ThetaParameter)
    {
#ifdef DEBUG
    qDebug()<<"Theta parameter was not satisfied";
#endif
        return true;
    }
#ifdef DEBUG
    qDebug()<<"Can combine two tiles";
    qDebug()<<"-------------------------------------------------------------------------------------------------";
#endif

    return false;
}

int Simulator_2HAM::getBondStrength(ActiveTile & t1, ActiveTile & t2, direction boundary)
/*
 Post-Condition: returns the highest bond strenghth of tile t1 and t2 at specified direction of tile t1
 */
{
#ifdef DEBUG
    qDebug()<<"-------------------------------------------------------------------------------------------------";
    qDebug()<<"Inside getBondStrength function";
#endif
    int strength = 0;
    foreach(int label1, t1.getActiveLabels(boundary))
    {
        foreach(int label2, t2.getActiveLabels((direction)((boundary + 2)%4)))
        {
            if(label1 + label2 == 0)
            {
                strength += StrengthMap[label1];
            }
        }
    }
#ifdef DEBUG
    qDebug()<<"Returning strength value: "<<strength;
    qDebug()<<"-------------------------------------------------------------------------------------------------";
#endif
    return strength;

}

void Simulator_2HAM::tileModificationFunction(AssemblyTile & T, QList<boundaryPoint *> *boundary)
/*
 Post-Condition: Apply tile modification function to tile T, also make boundary list empty at the end
 */
{
#ifdef DEBUG
    qDebug()<<"-------------------------------------------------------------------------------------------------";
    qDebug()<<"Inside tileModificationFunction";
#endif
    foreach(boundaryPoint* next, *boundary) //process every boundary
    {
#ifdef DEBUG
    qDebug()<<"Processing next boundary point";
#endif
        ActiveTile* mainTile = T.getTileFromCoordinates(next->x_y); //get main tile of the boundary
        ActiveTile* connectedTile = mainTile->getNeighbor(next->side);  //get connected to the boundary tile

        foreach(Signal init, connectedTile->getInitiationSignals())  //for each initiation signal of the connected tile
        {
#ifdef DEBUG
    qDebug()<<"Processing next initiation signal of the connected tile: "<<init.label;
#endif

            if(init.Target != (direction)((next->side + 2)%4))// process only initiation signals that point to the boundary direction
            {
#ifdef DEBUG
    qDebug()<<"This signal points in the wrong direction";
#endif
                continue;
            }

            //else tell ActiveTile to process signal
            mainTile->processSignal(next->side, init);

            //remove initiation signal, since it was processed
            connectedTile->RemoveInitiationSignal(init);


        }

        foreach(Signal init, mainTile->getInitiationSignals())  //next, pass all initiation signals from the maintile to the connectedtile
        {
#ifdef DEBUG
    qDebug()<<"Processing next initiation signal of the main tile: "<<init.label;
#endif

            if(init.Target != (direction)(next->side))// process only initiation signals that point to the boundary direction
            {
#ifdef DEBUG
    qDebug()<<"This signal points in the wrong direction";
#endif
                continue;
            }

            //else tell ActiveTile to process signal
            connectedTile->processSignal((direction)((next->side + 2)%4), init);

            //remove initiation signal, since it was processed
            mainTile->RemoveInitiationSignal(init);

        }
#ifdef DEBUG
    qDebug()<<"Calling clearSide functions";
#endif
        //next, we can clear all signals that can't be used
        mainTile->clearSide(next->side);
        connectedTile->clearSide((direction)((next->side + 2)%4));

        //make boundary list empty
        boundary->removeOne(next);
        delete next;
    }
#ifdef DEBUG
    qDebug()<<"-------------------------------------------------------------------------------------------------";
#endif
}

QList<DisplayTile*> Simulator_2HAM::toDisplayTile(AssemblyTile * T)
{
    T->rotateToDefaultPosition(); //unrotate assembly tile if needed

    QList<DisplayTile*> displayTiles;

    if(T->getListOfActiveTiles().back()->getCoordinates().first < 0)
    {
        T->moveAssemblyTile(QPair<int, int>(abs(T->getListOfActiveTiles().back()->getCoordinates().first), 0));
    }
    if(T->getListOfActiveTiles().back()->getCoordinates().second < 0)
    {
        T->moveAssemblyTile(QPair<int, int>(0, abs(T->getListOfActiveTiles().back()->getCoordinates().second)));
    }

    for(QList<ActiveTile *>::const_iterator iter = T->getListOfActiveTiles().begin(); iter != T->getListOfActiveTiles().end(); iter++)
    {
        //DisplayTile t(10 + (*iter)->getCoordinates().first*100, 10 + (*iter)->getCoordinates().second*100, 100);
        DisplayTile *t = new DisplayTile(100);
        t->setPos(10 + (*iter)->getCoordinates().first*100, 10 + (*iter)->getCoordinates().second*100);
        for(int side = 0; side < 4; side++) //add labels and signals for each side
        {
            if(!(*iter)->getActiveLabels((direction)(side)).isEmpty())
            {
                for(QList<int>::const_iterator activeIter = (*iter)->getActiveLabels((direction)(side)).begin(); activeIter != (*iter)->getActiveLabels((direction)(side)).end(); activeIter++)
                {
                    t->addLabel(DisplayLabel(side, ColorMap[(*activeIter)], true));
                }
            }

            if(!(*iter)->getInactiveLabels((direction)(side)).isEmpty())
            {
                for(QList<int>::const_iterator inactiveIter = (*iter)->getInactiveLabels((direction)(side)).begin(); inactiveIter != (*iter)->getInactiveLabels((direction)(side)).end(); inactiveIter++)
                {
                    t->addLabel(DisplayLabel(side, ColorMap[(*inactiveIter)], false));
                }
            }

            if(!(*iter)->getActivationSignals((direction)(side)).isEmpty())
            {
                for(QList<Signal>::const_iterator activationIter = (*iter)->getActivationSignals((direction)(side)).begin(); activationIter != (*iter)->getActivationSignals((direction)(side)).end(); activationIter++)
                {
                    t->addSignal(DisplaySignal(side, (int)(*activationIter).Target, ColorMap[(*activationIter).label], true));
                }
            }

            if(!(*iter)->getTransmissionSignals((direction)(side)).isEmpty())
            {
                for(QList<Signal>::const_iterator transmIter = (*iter)->getTransmissionSignals((direction)(side)).begin(); transmIter != (*iter)->getTransmissionSignals((direction)(side)).end(); transmIter++)
                {
                    t->addSignal(DisplaySignal(side, (int)(*transmIter).Target, ColorMap[(*transmIter).label], false));
                }
            }
        }
        //add initiation signals
        if(!(*iter)->getInitiationSignals().isEmpty())
        {
            for(QList<Signal>::const_iterator initIter = (*iter)->getInitiationSignals().begin(); initIter != (*iter)->getInitiationSignals().end(); initIter++)
            {
                t->addSignal(DisplaySignal(-1, (int)(*initIter).Target, ColorMap[(*initIter).label], false));
            }
        }

        displayTiles.append(t); //append tile to the list
    }

    return displayTiles;
}

QList<SetOfAssemblyTiles *> &Simulator_2HAM::getAssemblies()
//Get the list of all sets of assembly tiles
{
    return this->manager.getListOfSets();
}
