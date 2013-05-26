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

#include "ActiveTile.h"
    
	ActiveTile::ActiveTile()
	/*
		Default Constructor
		Post-Conditions: New tile object with empty sets of labels and signals was created
	*/
	{
		TileID = counter;
		counter++;

	}

    ActiveTile::ActiveTile(QList<QSet<QString> > &ActiveLabels, QList<QSet<QString> >  InactiveLabels, QSet<Signal> &ActivationSignals, QSet<Signal> &TransmissionSignals)
    /*
     Constructor with neighbors being not specified
     Post-Conditions: New tile object with Active labels, Inactive labels, Activation signals, and Transmission signals was created. Neighbor pointers are set to null
     */
    {
        TileID = counter;
        counter++;

        this -> ActiveLabels = ActiveLabels;
        this -> InactiveLabels = InactiveLabels;
        this -> ActivationSignals = ActivationSignals;
        this -> TranmissionSignals = TranmissionSignals;

    }
    ActiveTile::ActiveTile(QList<QSet<QString> > &ActiveLabels, QList<QSet<QString> >  InactiveLabels, QSet<Signal> &ActivationSignals, QSet<Signal> &TransmissionSignals,
                           ActiveTile * X,
                           ActiveTile * Y,
                           ActiveTile * _X,
                           ActiveTile * _Y)
	/*
		Constructor with defined tile's parameters.
		Post-Conditions: New tile object with Active labels, Inactive labels, Activation signals, and Transmission signals was created
	*/
	{
		TileID = counter;
		counter++;
		
		this -> ActiveLabels = ActiveLabels;
		this -> InactiveLabels = InactiveLabels;
		this -> ActivationSignals = ActivationSignals;
		this -> TranmissionSignals = TranmissionSignals;
		
		this -> X = X;
		this -> Y = Y;
		this -> _X = _X;
		this -> _Y = _Y;

	}
	ActiveTile::~ActiveTile()
	/*
		Default destcrutor
	*/
	{}
	
    void ActiveTile::setCoordinates(QPair<int, int> coord)
	/*
		Post-Conditions: Object's coordinates were changed
	*/
	{
		this->X_YCoordinates = coord;

	}
    void ActiveTile::setNeighbor(coordinate neigh, ActiveTile * newTile)
	/*
		Post-Conditions: Object neighbor marked by integer neigh is replaced with newTile
	*/
	{
		switch(neigh)
		{
		case x: this->X = newTile; break;
		case y: this->Y = newTile; break;
		case _x: this->_X = newTile; break;
		case _y: this->_Y = newTile; break;
        default: qDebug("Invalid coordinate for neighbor\n"); break;

		}
	}

       void ActiveTile::AddActiveLabel(coordinate side, QString label)
	/*
		Post-Conditions: New active label is added to a particular side
	*/
	   {
		   
	   }
    void ActiveTile::AddActiveLabels(coordinate side, QString labels[], int n)
	/*
		Post-Conditions: n new active labels are added to a particular side
	*/
	{

	}
    void ActiveTile::RemoveActiveLabel(coordinate side, QString label)
	/*
		Post-Conditions: Active label is removed from a side
	*/
	{

	}
    void ActiveTile::RemoveActiveLabels(coordinate side, QString labels[], int n)
	/*
		Post-Conditions: n active labels are removed from a side
	*/
	{

	}
    void ActiveTile::AddInactiveLabel(coordinate side, QString label)
	/*
		Post-Conditions: New inactive label is added to a particular side
	*/
	{

	}
    void ActiveTile::AddInactiveLabels(coordinate side, QString labels[], int n)
	/*
		Post-Conditions: n new inactive labels are added to a particular side
	*/
	{

	}
    void ActiveTile::RemoveInactiveLabel(coordinate side, QString label)
	/*
		Post-Conditions: Inactive label is removed from a side
	*/
	{

	}
    void ActiveTile::RemoveInactiveLabels(coordinate side, QString labels[], int n)
		/*
		Post-Conditions: n inactive labels are removed from a side
	*/
	{

	}
	void ActiveTile::AddActivationSignal(Signal s)
	/*
		Post-Conditions: Activation signal was added
	*/
	{

	}

    void ActiveTile::AddActivationSignals(Signal s[], int n)
	/*
		Post-Conditions: n activation signals were added
	*/
	{

	}
	void ActiveTile::RemoveActivationSignal(Signal s)
	/*
		Post-Conditions: if s belongs to the tile, it is removed
	*/
	{

	}

	void ActiveTile::RemoveActivationSignals(Signal s[], int n)
	/*
		Post-Conditions: for n activation signals, if signal belongs to the tile, it is removed
	*/
	{

	}
	//Similarly for transmission signals
    void ActiveTile::AddTransmissionSignal(Signal s)
	{

	}
	void AddTransmissionSignals(Signal s[], int n)
	{

	}
	void RemoveTransmissionSignal(Signal s)
	{

	}
	void RemoveTransmissionSignals(Signal s[], int n)
	{

	}

	int ActiveTile::getId()
	/*
		Post-Conditions: Tile's id is returned
	*/
	{
		return 0;
	}
    QSet<QString> ActiveTile::getActiveLabels(int side)
	/*
		Post-Conditions: Active labels of a particular side are returned
	*/
	{
        QSet<QString> empty;
		return empty;
	}

    QSet<QString> ActiveTile::getInactiveLabels(int side)
	/*
		Post-Conditions: Inactive labels of a particular side are returned
	*/
	{
        QSet<QString> empty;
			return empty;
	}
    QSet<Signal> ActiveTile::getActivationSignals()
	/*
		Post-Conditions: Activation signals of a tile are returned
	*/
	{
        QSet<Signal> empty;
		return empty;
	}
    QSet<Signal> ActiveTile::getTransmissionSignals()
	/*
		Post-Conditions: Transmission signals of a tile are returned
	*/
	{
            QSet<Signal> empty;
		return empty;
	}
    QPair<int, int> ActiveTile::getCoordinates()
	/*
		Post-Conditions: Tile's coordinates are returned
	*/
	{
        QPair<int, int> empty(0, 0);
		return empty;
	}

	ActiveTile * ActiveTile::getNeighbor(coordinate from)
	/*
		Post-Conditions: Tile's neighbor on a particular side is returned; if tile does not have a neighbor, null is returned
	*/
	{
		ActiveTile T;
		return &T;
	}

    void ActiveTile::rotateTile(QPair<int, int> referencePoint, int times)
	/*
		Post-Conditions: Tile is rotated against reference point required number of times
	*/
	{

	}
    void ActiveTile::moveTile(QPair<int, int> shift)
	/*
		Post-Conditions: Tile is translated according to the shift coordinates
	*/

	{

	}
