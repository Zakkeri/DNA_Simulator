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
    
	// Default Constructor

	ActiveTile::ActiveTile()
	{
        TileID = ActiveTile::counter;
        ActiveTile::counter++;

	}



	// Constructor with neighbors being not specified
	// Post-Conditions: New tile object with Active labels, Inactive labels, Activation signals, and Transmission signals was created. Neighbor pointers are set to null
    
    ActiveTile::ActiveTile(const QList<QList<int> > &ActiveLabels, const QList<QList<int> >  &InactiveLabels,
                           const QList<QList<Signal> > &ActivationSignals, const QList<QList<Signal> > &TransmissionSignals)
    {
        TileID = ActiveTile::counter;
        ActiveTile::counter++;

		for(int i = 0; i < 4; i++)
		{
            Side[i].ActiveLabels = ActiveLabels[i];
            Side[i].InactiveLabels = InactiveLabels[i];
            Side[i].ActivationSignals = ActivationSignals[i];
            Side[i].TransmissionSignals = TransmissionSignals[i];
		}

    }



	// Contructor that makes a deep copy of another tile
	// Post-Conditions: New tile is created that is the same as otherTile

	ActiveTile::ActiveTile(const ActiveTile &otherTile)
	{
        X_Y_Coordinates = otherTile.X_Y_Coordinates;
		TileID = counter;
		counter++;
	}



	// Default Destructor
	ActiveTile::~ActiveTile(){}


	// Post-Conditions: Object's coordinates were changed

    void ActiveTile::setCoordinates(QPair<int, int> coord)
	{
        this->X_Y_Coordinates = coord;

	}


	// Post-Conditions: Object neighbor marked by integer neigh is replaced with newTile

    void ActiveTile::setNeighbor(direction neigh, ActiveTile * newTile)
	{
        this->Neighbors[neigh] = newTile;
	}



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
        this->Side[side].ActiveLabels.removeOne(label);
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
        this->Side[side].InactiveLabels.removeOne(label);
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

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Similarly for initiation signals
    void ActiveTile::AddInitiationSignal(direction side, Signal signal)
    {

    }

    void ActiveTile::AddInitiationSignals(direction side, QList<Signal> signalList)
    {

    }

    void ActiveTile::RemoveInitiationSignal(direction side, Signal signal)
    {

    }

    void ActiveTile::RemoveInitiationSignals(direction side, QList<Signal> signalList)
    {

    }


	// Post-Conditions:  Returns a list of a side's Labels or Signals

    QList<int> ActiveTile::getActiveLabels(direction side)
	{
		return Side[side].ActiveLabels;
	}

    QList<int> ActiveTile::getInactiveLabels(direction side)
	{
		return Side[side].InactiveLabels;
	}

    QList<Signal> ActiveTile::getActivationSignals(direction side)
	{
		return Side[side].ActivationSignals;
	}

    QList<Signal> ActiveTile::getTransmissionSignals(direction side)
	{
		return Side[side].TransmissionSignals;
	}

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QList<Signal> ActiveTile::getInitiationSignals()
    {

    }


	// Post-Conditions: Get functions for various properties, they return their appropriate type

	int ActiveTile::getId()
	{
		return TileID;
	}

    QPair<int, int> ActiveTile::getCoordinates()
	{
        QPair<int, int> empty(0, 0);
		return empty;
	}

    ActiveTile * ActiveTile::getNeighbor(direction from)
	{
        return this->Neighbors[from];
	}



    // Post-Conditions: Tile is rotated counterclockwise required number of times
    void ActiveTile::rotateTile(int times=1)
    {
        if(times > 1) rotateTile(times - 1);

        TileSide tempSide;
        tempSide = Side[1];
        Side[1] = Side[0];
        Side[0] = Side[3];
        Side[3] = Side[2];
        Side[2] = tempSide;
    }



	// Post-Conditions: Tile is translated according to the shift coordinates
    void ActiveTile::moveTile(QPair<int, int> shift)
	{
		X_Y_Coordinates.first += shift.first;
		X_Y_Coordinates.second += shift.second;
	}


    // Operator == for signals
    // Post-Conditions:  Returns true iff the signal and the target are the same
    bool signal::operator ==(const signal otherSignal) const
    {
        if(this->label == otherSignal.label && this->Target == otherSignal.Target) return true;
        return false;
    }
