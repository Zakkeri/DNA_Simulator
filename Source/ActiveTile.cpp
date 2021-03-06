//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : ActiveTile.cpp
//  @ Date : 5/20/2013
//  @ Author : 
//
//

#include "../Headers/ActiveTile.h"


#ifdef DEBUG
    int ActiveTile::ID = 0;   //unique id for everytile
#endif
	// Default Constructor

	ActiveTile::ActiveTile()
	{
#ifdef DEBUG

    this->uniqueID = ActiveTile::ID;
    ActiveTile::ID++;
#endif
        TileID = 0;
        parent = 0; //set parent to 0
	}



	// Constructor with neighbors being not specified
	// Post-Conditions: New tile object with Active labels, Inactive labels, Activation signals, and Transmission signals was created. Neighbor pointers are set to null
    
    ActiveTile::ActiveTile(const QList<QList<int> > &ActiveLabels, const QList<QList<int> >  &InactiveLabels,
                           const QList<QList<Signal> > &ActivationSignals, const QList<QList<Signal> > &TransmissionSignals,
                           const QList<Signal> &Initiation, int ID)
    {
#ifdef DEBUG

    this->uniqueID = ActiveTile::ID;
    ActiveTile::ID++;
#endif
        TileID = ID;
        parent = 0; //set parent to 0
        rotation = 0;
		for(int i = 0; i < 4; i++)
		{
            Side[i].ActiveLabels = ActiveLabels[i];
            Side[i].InactiveLabels = InactiveLabels[i];
            Side[i].ActivationSignals = ActivationSignals[i];
            Side[i].TransmissionSignals = TransmissionSignals[i];
		}

        InitiationSignals = Initiation;

        /*for(int i = 0; i < 4; i++)
        {
            Neighbors[i] = NULL;
        }*/
    }



	// Contructor that makes a deep copy of another tile
	// Post-Conditions: New tile is created that is the same as otherTile

	ActiveTile::ActiveTile(const ActiveTile &otherTile)
	{
#ifdef DEBUG

    this->uniqueID = ActiveTile::ID;
    ActiveTile::ID++;
#endif
        this->parent = 0;    //set parent to NULL, so it will be set manualy
        this->rotation = otherTile.rotation;
        X_Y_Coordinates = otherTile.X_Y_Coordinates;
        TileID = otherTile.getId();
        this->InitiationSignals = otherTile.InitiationSignals;
        for(int dir = 0; dir < 4; dir++)
        {
            this->Side[dir].ActivationSignals = otherTile.Side[dir].ActivationSignals;
            this->Side[dir].ActiveLabels = otherTile.Side[dir].ActiveLabels;
            this->Side[dir].InactiveLabels = otherTile.Side[dir].InactiveLabels;
            this->Side[dir].TransmissionSignals = otherTile.Side[dir].TransmissionSignals;
        }

        //So far, neighbors are all equal to NULL
      /*  for(int i = 0; i < 4; i++)
        {
            Neighbors[i] = NULL;
        }*/
	}



	// Default Destructor
	ActiveTile::~ActiveTile(){}


	// Post-Conditions: Object's coordinates were changed

    void ActiveTile::setCoordinates(QPair<int, int> coord)
	{
        this->X_Y_Coordinates = coord;

	}

/*
	// Post-Conditions: Object neighbor marked by integer neigh is replaced with newTile

    void ActiveTile::setNeighbor(direction neigh, ActiveTile * newTile)
	{
        this->Neighbors[neigh] = newTile;
	}
*/


	// Post-Conditions: Adds/removes active labels or a list of active labels from a given side

    void ActiveTile::AddActiveLabel(direction side, int label)
	{
		Side[side].ActiveLabels << label;
	}

    void ActiveTile::AddActiveLabels(direction side, QList<int> labels)
	{
		Side[side].ActiveLabels << labels;
	}

    void ActiveTile::RemoveActiveLabel(direction side, int label)
	{
        if(!this->Side[side].ActiveLabels.removeOne(label))
        {
            this->Side[side].ActiveLabels.removeOne(label);
        }
	}

    void ActiveTile::RemoveActiveLabels(direction side, QList<int> labels)
	{
        int labelToRemove;

        foreach(labelToRemove, labels)
        {
            this->Side[side].ActiveLabels.removeOne(labelToRemove);
        }
	}


	// Post-Conditions: Adds/removes inactive labels or a list of inactive labels from a given side

    void ActiveTile::AddInactiveLabel(direction side, int label)
	{
        Side[side].InactiveLabels << label;
	}

    void ActiveTile::AddInactiveLabels(direction side, QList<int> labels)
	{
		Side[side].InactiveLabels << labels;
	}

    void ActiveTile::RemoveInactiveLabel(direction side, int label)
	{
        if(!this->Side[side].InactiveLabels.removeOne(label))
        {
            this->Side[side].InactiveLabels.removeOne(-label);
        }
	}

    void ActiveTile::RemoveInactiveLabels(direction side, QList<int> labels)
	{
        int labelToRemove;

        foreach(labelToRemove, labels)
        {
            this->Side[side].InactiveLabels.removeOne(labelToRemove);
        }
	}



	// Post-Conditions: Adds/removes activation signals or a list of activation signals from a given side
	//                  if the activation signal(s) exist on that side
	//
	// Please Note:  Only 1 side may be affected per call of the function, even if a list is being added/removed

    void ActiveTile::AddActivationSignal(direction side, Signal signal)
	{
        Side[side].ActivationSignals << signal;
	}

    void ActiveTile::AddActivationSignals(direction side, QList<Signal> signalList)
	{
        Side[side].ActivationSignals << signalList;
	}

    void ActiveTile::RemoveActivationSignal(direction side, Signal signal)
	{
        Side[side].ActivationSignals.removeOne(signal);
	}

    void ActiveTile::RemoveActivationSignals(direction side, QList<Signal> signalList)
    {
        Signal signalToRemove(0,x);

        foreach(signalToRemove, signalList)
        {
            this->Side[side].ActivationSignals.removeOne(signalToRemove);
        }
	}



	// Similarly for transmission signals

    void ActiveTile::AddTransmissionSignal(direction side, Signal signal)
	{
        this->Side[side].TransmissionSignals << signal;
	}

    void ActiveTile::AddTransmissionSignals(direction side, QList<Signal> signalList)
	{
        Side[side].TransmissionSignals << signalList;
	}

    void ActiveTile::RemoveTransmissionSignal(direction side, Signal signal)
	{
        Side[side].TransmissionSignals.removeOne(signal);
	}

    void ActiveTile::RemoveTransmissionSignals(direction side, QList<Signal> signalList)
	{
        Signal signalToRemove(0,x);

        foreach(signalToRemove, signalList)
        {
            this->Side[side].TransmissionSignals.removeOne(signalToRemove);
        }
	}


    // Similarly for initiation signals
    void ActiveTile::AddInitiationSignal(Signal signal)
    {
        InitiationSignals << signal;
    }

    void ActiveTile::AddInitiationSignals(QList<Signal> signalList)
    {
        InitiationSignals << signalList;
    }

    void ActiveTile::RemoveInitiationSignal(Signal signal)
    {
        InitiationSignals.removeOne(signal);
    }

    void ActiveTile::RemoveInitiationSignals(QList<Signal> signalList)
    {
        Signal signalToRemove(0,x);

        foreach(signalToRemove, signalList)
        {
            InitiationSignals.removeOne(signalToRemove);
        }
    }


    /*Post-Conditions: signal is received from the side and is processed. As a result:
    1) If corresponding activation signal is found, then inactive label is activated, else
    2) If corresponding transmission signal is found, then initiation signal is passed to the next tile,
        or initiation signal is added to the tile, else
    3) No corresponding signal is found
    */
    void ActiveTile::processSignal(direction side, Signal toProcess)
    {
        foreach(Signal activation, Side[side].ActivationSignals) //first, check if initiation signal have corresponding activation signal
         {
             if(activation.label != toProcess.label && -activation.label != toProcess.label)   //if labels don't match, pick next one
             {
                continue;
             }
            else
             {
                activate(side, activation); //else activate a corresponding label
                return; //and return, since we are done
                        //Should it return here?  There could be both a tramission and
                        //activation signal from the same side.
             }
         }

        foreach(Signal transm, Side[side].TransmissionSignals)  //next, check if any transmission signal can be used
        {
            if(transm.label != toProcess.label && -transm.label != toProcess.label) //if labels don't match, pick next one
            {
                continue;
            }
            else    //labels do match
            {
                ActiveTile* neighbor = getNeighbor(transm.Target);  //try to get a neighbor
                if(neighbor != 0) //check if there is a neighbor
                {
                    neighbor->processSignal((direction)((transm.Target + 2)%4), transm); //if neighbor exist, then send the transmission signal to it
                }
                else    //if there is no neighbor
                {
                    AddInitiationSignal(transm);
                }

                RemoveTransmissionSignal(side, transm); //remove signal, since it was processed

                return;//and return, since we are done
            }
        }

        return; //if no matching signal is found, then just return
    }

    //Pre-Conditions: On the corresponding side, all initiation signals were received and processed
    //Post-Conditions: all activation signals and corresponding inactive labels that can't be activated are removed, and all transmission signals that can't be transmited are also removed
    void ActiveTile::clearSide(direction side)
    {
        ActiveTile *neighbor = getNeighbor(side);    //get a hold on the neighbor tile

        QList<Signal> listOfTranmsmSignals; //list that will hold all transmission signals of the neighbor tile

        //construct the list first
        for(int dir = 0; dir < 4; dir++) //for every side of the neighbor tile
        {
            if(dir == (side + 2)%4) //skip the boundary direction
            {
                continue;
            }
            foreach(Signal transm, neighbor->getTransmissionSignals((direction)dir)) //for every transmission signal of that side
            {
                if(transm.Target == (direction)((side + 2)%4))// if signal goes on the boundary direction, then
                {
                    listOfTranmsmSignals << transm; //add it to the list
                }
            }
        }

        foreach(Signal activ, Side[side].ActivationSignals) //process all activation signals, and remove if necessary
        {
            if(listOfTranmsmSignals.contains(Signal(activ.label, (direction)((side + 2)%4))))   //if there is a corresponding transmission signal
            {
                listOfTranmsmSignals.removeOne(Signal(activ.label, (direction)((side + 2)%4))); //remove signal from the list
                // This is another place where having both an activation signal and trasmission signal
                // from the same side could cause problems in the code.
                continue; //check for next activation signal
            }
            else    //else remove activation signal and corresponding inactive label
            {
                RemoveActivationSignal(side, activ);

                // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                // Check if there are any other activation signal that can activate the label
                bool removeLabel = true;    //flag for label deletion
                for(int dir = 0; dir < 4; dir++)    //go through each side
                {
                    if(dir == (side + 2)%4) //skip the side to which signals are going
                    {
                        continue;
                    }
                    foreach (Signal activ2, Side[dir].ActivationSignals)//for each activation signal
                    {
                        if(activ2.Target == activ.Target && activ2.label == activ.label)//check if it is pointing in the same direction and has the same label
                        {
                            removeLabel = false;    //if so, then we don't want to remove inactive label, since it can still be activated
                            break;  //break from the loop, since decision was made
                        }
                    }
                    if(!removeLabel)    //if we are not removing label, then break from the loop
                    {
                        break;
                    }
                }
                if(removeLabel) //if we are removing label, then remove it
                {
                    RemoveInactiveLabel(activ.Target, activ.label);
                }
            }
        }

        foreach(Signal transm, Side[side].TransmissionSignals)  //process all transmission signals, and remove if necessary
        {
            if(listOfTranmsmSignals.contains(Signal(transm.label, (direction)((side + 2)%4)))) //check if transmission signal can be received
            {
                ActiveTile *neighborForTransm = getNeighbor(transm.Target);//get neighbor tile to which signal is supposed to be transmited
                if(neighborForTransm == 0)  //if there is no neighbor, then
                {
                    listOfTranmsmSignals.removeOne(Signal(transm.label, (direction)((side + 2)%4))); //remove signal, since we need to keep it
                    continue;
                }

                //else check if signal can be transmited
                bool canTransm = false;
                foreach(Signal activ, neighborForTransm->getActivationSignals((direction)((transm.Target + 2)%4))) //check for activation signals first
                {
                    if(activ.label == transm.label) //if labels match
                    {
                        canTransm = true;  //then we can transmit
                        break;
                    }
                }

                if(canTransm)   //if can transmit, then
                {
                    listOfTranmsmSignals.removeOne(Signal(transm.label, (direction)((side + 2)%4))); //remove signal, since we need to keep it
                    continue;
                }

                //else, check for transmission signals
                // As it's written, it's going to check for both trasmission signals and activation
                // signals regardless of whether it finds them first, so isn't it redundant to use
                // the same if statement twice?

                foreach(Signal neighTransm, neighborForTransm->getTransmissionSignals((direction)((transm.Target + 2)%4)))
                {
                    if(neighTransm.label == transm.label)//if can transmit
                    {
                        canTransm = true;
                        break;
                    }
                }

                if(canTransm) //if can transmit, then
                {
                    listOfTranmsmSignals.removeOne(Signal(transm.label, (direction)((side + 2)%4))); //remove signal, since we need to keep it
                    continue;
                }

                //else, I can not transmit signal, so I need to remove the whole chain of transmission signals
                listOfTranmsmSignals.removeOne(Signal(transm.label, (direction)((side + 2)%4))); //remove signal, since it will be removed
                RemoveTransmissionSignal(side, transm); //remove transmission signal in current tile

                // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!New Function to implement
                getNeighbor(side)->removeUpwardChain((direction)((side + 2)%4), transm.label);
            }

            else    //if transmision signal can not be received, then remove all transmission and activation signals down the chain
            {
                RemoveTransmissionSignal(side, transm);//remove transmission signal in current tile

                if(getNeighbor(transm.Target) != 0) //if there is a tile for transmission signal, then delete all not needed signals and side labels
                {
                    // !!!!!!!!!!!!!!!!!!New Function to Implement
                    getNeighbor(transm.Target)->removeDownwardChain((direction)((transm.Target + 2)%4), transm.label);
                }
            }
        }

    }

    //Post-Condition: All transmission signals that point in the corresponding direction with corresponding label are removed. Function is recursively called on the removed signals' origin
    void ActiveTile::removeUpwardChain(direction toSide, int label)
    {
        for(int dir = x; dir < 4; dir++)  //for every side, chack for transmission signals pointing toSide
        {
            if(dir == toSide)   //skip toSide
            {
                continue;
            }

            foreach(Signal transm, Side[dir].TransmissionSignals)
            {
                if(transm.Target == toSide && transm.label == label) //if it is a correct transmission signal, then
                {
                    RemoveTransmissionSignal((direction)dir, transm);  //remove it
                    getNeighbor((direction)dir)->removeUpwardChain((direction)((dir + 2)%4), label); //also remove the whole chain from above
                }
            }
        }
    }

    //Post-Condition: All transmission and activation signals that start from the corresponding direction with corresponding label are removed. Function is recursively called on the removed signals' target
    //Also, all inactive labels to which activation signals were pointing are removed
    void ActiveTile::removeDownwardChain(direction fromSide, int label)
    {
        //first check for activation signals
        foreach(Signal activ, Side[fromSide].ActivationSignals)
        {
            if(activ.label == label)    //if it is a correct activation signal, then
            {
                RemoveActivationSignal(fromSide, activ); // remove it
                RemoveInactiveLabel(activ.Target, label);   //and remove corresponding inactive label
            }
        }

        //next, remove all transmission signals

        foreach(Signal transm, Side[fromSide].TransmissionSignals)
        {
            if(transm.label == label)   //if it is a correct transmission signal, then
            {
                RemoveTransmissionSignal(fromSide, transm); // remove it
                getNeighbor(transm.Target)->removeDownwardChain((direction)((transm.Target + 2)%4), label); //and remove all signals down the chain
            }
        }
    }

	// Post-Conditions:  Returns a list of a side's Labels or Signals

    QList<int> &ActiveTile::getActiveLabels(direction side)
	{
		return Side[side].ActiveLabels;
	}

    QList<int> &ActiveTile::getInactiveLabels(direction side)
	{
		return Side[side].InactiveLabels;
	}

    QList<Signal> &ActiveTile::getActivationSignals(direction side)
	{
		return Side[side].ActivationSignals;
	}

    QList<Signal> &ActiveTile::getTransmissionSignals(direction side)
	{
		return Side[side].TransmissionSignals;
	}


    QList<Signal> &ActiveTile::getInitiationSignals()
    {
        return this->InitiationSignals;
    }


    //Post-Conditions: required signal activates corresponding side. That is move inactive label to active set, remove activation signal
    void ActiveTile::activate(direction sourceSide, Signal activationSignal)
    {
        Side[sourceSide].ActivationSignals.removeOne(activationSignal);
        if(Side[activationSignal.Target].InactiveLabels.removeOne(activationSignal.label))
        {
            Side[activationSignal.Target].ActiveLabels << activationSignal.label;
            if(this->getNeighbor(activationSignal.Target) == 0)
            {
                parent->addFreeSide(freeActiveLabel(activationSignal.label, activationSignal.Target, this->getCoordinates()));
            }
        }
        else if(Side[activationSignal.Target].InactiveLabels.removeOne(-activationSignal.label))
        {
            Side[activationSignal.Target].ActiveLabels << -activationSignal.label;
            if(this->getNeighbor(activationSignal.Target) == 0)
            {
                parent->addFreeSide(freeActiveLabel(-activationSignal.label, activationSignal.Target, this->getCoordinates()));
            }
        }
    }

	// Post-Conditions: Get functions for various properties, they return their appropriate type

    int ActiveTile::getId() const
	{
		return TileID;
	}

    QPair<int, int> ActiveTile::getCoordinates()
	{
        return X_Y_Coordinates;
	}

    //Pre-Conditions: parent is not equal to NULL
    //Post-Condition: Neighbor of current tile from given direction is returned
    ActiveTile * ActiveTile::getNeighbor(direction from)
	{
        switch(from)
        {
        case x:

            return this->parent->getTileFromCoordinates(QPair<int, int>(this->X_Y_Coordinates.first + 1, this->X_Y_Coordinates.second));

            break;

        case y:

            return this->parent->getTileFromCoordinates(QPair<int, int>(this->X_Y_Coordinates.first, this->X_Y_Coordinates.second + 1));

            break;

        case _x:

            return this->parent->getTileFromCoordinates(QPair<int, int>(this->X_Y_Coordinates.first - 1, this->X_Y_Coordinates.second));

            break;

        case _y:

            return this->parent->getTileFromCoordinates(QPair<int, int>(this->X_Y_Coordinates.first, this->X_Y_Coordinates.second - 1));

            break;
        default:
            return NULL;
        }
	}



    // Post-Conditions: Tile is rotated counterclockwise required number of times
    void ActiveTile::rotateTile(int times=1)
    {
        if(times == 0) return;
        if(times > 1) rotateTile(times - 1);

        TileSide tempSide;
        tempSide = Side[1];
        Side[1] = Side[0];
        Side[0] = Side[3];
        Side[3] = Side[2];
        Side[2] = tempSide;

        //rotate each signal
        for(int i = 0; i < 4; i++)
        {
            for(QList<Signal>::iterator it = Side[i].ActivationSignals.begin(); it != Side[i].ActivationSignals.end(); it++)
            {
                it->Target = (direction)((it->Target + 1) % 4);
            }
            for(QList<Signal>::iterator it = Side[i].TransmissionSignals.begin(); it != Side[i].TransmissionSignals.end(); it++)
            {
                it->Target = (direction)((it->Target + 1) % 4);
            }
        }
        for(QList<Signal>::iterator it = this->InitiationSignals.begin(); it != this->InitiationSignals.end(); it++)
        {
            it->Target = (direction)((it->Target + 1) % 4);
        }
        this->X_Y_Coordinates = QPair<int, int>(-this->X_Y_Coordinates.second, this->X_Y_Coordinates.first);
        rotation = (rotation + 1) % 4;
    }



	// Post-Conditions: Tile is translated according to the shift coordinates
    void ActiveTile::moveTile(QPair<int, int> shift)
	{
		X_Y_Coordinates.first += shift.first;
		X_Y_Coordinates.second += shift.second;
	}



    // Post-Conditions:  Tile is translated to the given coordinates
    void ActiveTile::moveTo(QPair<int,int> finalCoords)
    {
        X_Y_Coordinates.first = finalCoords.first;
        X_Y_Coordinates.second = finalCoords.second;
    }



    //Post-Conditions: Set functions for various properties
    void ActiveTile::setId(int id)
    {
        this->TileID = id;
    }



    // Post-Conditions: Returns true iff the tiles have the same ID
    bool ActiveTile::operator ==(ActiveTile &otherTile)
    {
        if(this->TileID == otherTile.TileID) return true;
        return false;
    }

    // Operator == for signals
    // Post-Conditions:  Returns true iff the signal and the target are the same
    bool signal::operator ==(const signal otherSignal) const
    {
        if(this->label == otherSignal.label && this->Target == otherSignal.Target) return true;
        return false;
    }

    // Post-Conditions: Sets parent of this Active Tile
    void ActiveTile::setParent(AssemblyTile* p)
    {
        parent = p;

    }

    int ActiveTile::getRotation()
    {
        return this->rotation;
    }
