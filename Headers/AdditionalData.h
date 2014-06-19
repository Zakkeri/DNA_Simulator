#ifndef ADDITIONALDATA_H
#define ADDITIONALDATA_H

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



struct freeActiveLabel
{
    freeActiveLabel(int l, direction dir, QPair<int, int> xy)
        :label(l), side(dir), xyCoord(xy)
    {

    }

    bool match(const freeActiveLabel& l)const
    {
        return this->label + l.label == 0;
    }

    bool operator==(const freeActiveLabel other)
    {
        return (this->label == other.label) && (this->side == other.side) && (this->xyCoord == other.xyCoord);
    }

    int label;
    direction side;
    QPair<int, int> xyCoord;
};


// Needed to move this here because the compiler was complaining.
struct boundaryPoint
{
    boundaryPoint(const bool tile,const QPair<int, int> coord,const direction dir)
        : isT1(tile), x_y(coord), side(dir)
    {

    }
    bool isT1;  //to tell from which assembly tile the boundary point is infered
    QPair<int, int> x_y; //coordinates of tile1 on the boundary point
    direction side; //where the boundary is
};

typedef struct fittingSpot
{
    fittingSpot(const QPair<int, int>& c1, const QPair<int, int> &c2,const int num)
        : firstTile(c1), secondtTile(c2), rotation(num)
    {

    }

    QPair<int, int> firstTile;
    QPair<int, int> secondtTile;
    int rotation;
}FitPlace;

#endif // ADDITIONALDATA_H
