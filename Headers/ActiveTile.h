//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : ActiveTile.h
//  @ Date : 5/20/2013
//  @ Author : 
//
//


#ifndef _ACTIVETILE_H
#define _ACTIVETILE_H

#include<QSet>
#include<QList>
#include<QPair>
#define DEBUG
using namespace std;

enum direction{x, y, _x, _y};	//for tile's sides

typedef struct signal
{

    int label;
    direction Target;

    // I'm fairly certain this overload is required for removeOne() to work
    // Post-Conditions:  Returns true iff labels and targets are the same
    bool operator == (const signal otherSignal) const;

    signal(int l, direction T)	//Signal constructor
        :label(abs(l)), Target(T){}

} Signal;

typedef struct TileSide
{
    QList<Signal> ActivationSignals;
    QList<Signal> TransmissionSignals;
	QList<int> ActiveLabels;
	QList<int> InactiveLabels;

	// Default Contructor, makes a TileSide with no signals or labels
	// These should be populated later by the ActiveTile they're a part of
    //TileSide();

} TileSide;



class ActiveTile
{
public:

#ifdef DEBUG
    static int ID;   //unique id for everytile
#endif
	// Default Constructor
    ActiveTile();



	// Constructor with neighbors being not specified
	// Post-Conditions: New tile object with Active labels, Inactive labels, Activation signals, and Transmission signals was created. Neighbor pointers are set to null
    ActiveTile(const QList<QList<int> > &ActiveLabels, const QList<QList<int> > &InactiveLabels,
               const QList<QList<Signal> > &ActivationSignals, const QList<QList<Signal> > &TransmissionSignals,
               const QList<Signal> &Initiation, int ID);



	// Contructor that makes a deep copy of another tile
	// Post-Conditions: New tile is created that is the same as otherTile
	ActiveTile(const ActiveTile &otherTile);



	// Default Destructor
	~ActiveTile();



	// Post-Conditions: Object's coordinates were changed
    void setCoordinates(QPair<int, int> coord);



	// Post-Conditions: Object neighbor marked by integer neigh is replaced with newTile
    void setNeighbor(direction neigh, ActiveTile * newTile);



    // Post-Conditions: Adds/removes active labels or a list of active labels from a given side
    //
    // Please Note:  Only 1 side may be affected per call of the function,
    //               even if a list is being added/removed
    void AddActiveLabel(direction side, int label);
    void AddActiveLabels(direction side, QList<int> labels);
    void RemoveActiveLabel(direction side, int label);
    void RemoveActiveLabels(direction side, QList<int> labels);



	// Post-Conditions: Adds/removes inactive labels or a list of inactive labels from a given side
    void AddInactiveLabel(direction side, int label);
    void AddInactiveLabels(direction side, QList<int> labels);
    void RemoveInactiveLabel(direction side, int label);    // !!!!! Will need to remove both, positive and negative Labels!!!!
    void RemoveInactiveLabels(direction side, QList<int> labels);



	// Post-Conditions: Adds/removes activation signals or a list of activation signals from a given side
	//                  if the activation signal(s) exist on that side
	//
    // Please Note:  Only 1 side may be affected per call of the function,
    //               even if a list is being added/removed
    void AddActivationSignal(direction side, Signal signal);
    void AddActivationSignals(direction side, QList<Signal> signalList);
    void RemoveActivationSignal(direction side, Signal signal);
    void RemoveActivationSignals(direction side, QList<Signal> signalList);



	// Similarly for transmission signals
    void AddTransmissionSignal(direction side, Signal signal);
    void AddTransmissionSignals(direction side, QList<Signal> signalList);
    void RemoveTransmissionSignal(direction side, Signal signal);
    void RemoveTransmissionSignals(direction side, QList<Signal> signalList);


    // Similarly for initiation signals
    void AddInitiationSignal(Signal signal);
    void AddInitiationSignals(QList<Signal> signalList);
    void RemoveInitiationSignal(Signal signal);
    void RemoveInitiationSignals(QList<Signal> signalList);

	// Post-Conditions:  Returns a list of a side's Labels or Signals
    QList<int> &getActiveLabels(direction side);
    QList<int> &getInactiveLabels(direction side);
    QList<Signal> &getActivationSignals(direction side);
    QList<Signal> &getTransmissionSignals(direction side);
    QList<Signal> &getInitiationSignals();


    /*Post-Conditions: signal is received from the side and is processed. As a result:
    1) If corresponding activation signal is found, then inactive label is activated, else
    2) If corresponding transmission signal is found, then initiation signal is passed to the next tile,
        or initiation signal is added to the tile, else
    3) No corresponding signal is found
    */
    void processSignal(direction side, Signal toProcess);

    //Pre-Conditions: On the corresponding side, all initiation signals were received and processed
    //Post-Conditions: all activation signals and corresponding inactive labels that can't be activated are removed, and all transmission signals that can't be transmited are also removed
    void clearSide(direction side);


    //Post-Condition: All transmission signals that point in the corresponding direction with corresponding label are removed. Function is recursively called on the removed signals' origin
    void removeUpwardChain(direction toSide, int label);

    //Post-Condition: All transmission and activation signals that start from the corresponding direction with corresponding label are removed. Function is recursively called on the removed signals' target
    //Also, all inactive labels to which activation signals were pointing are removed
    void removeDownwardChain(direction fromSide, int label);

    //Post-Conditions: required signal activates corresponding side. That is move inactive label to active set, remove activation signal
    void activate(direction sourceSide, Signal activationSignal);

	// Post-Conditions: Get functions for various properties, they return their appropriate type
    int getId()const;
    QPair<int, int> getCoordinates();
    ActiveTile * getNeighbor(direction from);

    // Post-Conditions: Tile is rotated counterclockwise required number of times
    void rotateTile(int times);

    //Post-Conditions: Set functions for various properties
    void setId(int id);

	// Post-Conditions: Tile is translated according to the shift coordinates
    void moveTile(QPair<int, int> shift);

    // Post-Conditions:  Tile is translated to the given coordinates
    void moveTo(QPair<int,int> finalCoords);

    // Post-Conditions: Returns true iff the tiles have the same ID
    bool operator==(ActiveTile &otherTile);

private:
  //  static int counter;
	int TileID;
    QPair<int, int> X_Y_Coordinates;
    ActiveTile *Neighbors[4];
	TileSide Side[4];
    QList<Signal> InitiationSignals;

#ifdef DEBUG
    int uniqueID;   //unique id for everytile
#endif
};



#endif  //_ACTIVETILE_H
