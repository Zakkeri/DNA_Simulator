#ifndef DISPLAYTILE_H
#define DISPLAYTILE_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QList>
#include <QPainter>


// The type that a signal is will be stored in the DisplaySignal
// struct.  If a signal is an initiation signal, give it a
// source value of -1.  This helps because the only difference between
// how an activation signal and a transmission signal are drawn
// is the line type.

struct DisplaySignal
{
    int source, target;
    bool activation;
    QColor color;
    DisplaySignal(int s, int t, QColor c, bool active=false)
    {
        source = s;
        target = t;
        color = c;
        if(s != -1)
            activation = active;
        else
            activation = false;
    }

    bool operator==(const DisplaySignal &other) const{
        return (source == other.source && target == other.target && color == other.color && activation == other.activation);
    }

    bool operator<(const DisplaySignal &other) const{
        if(this->activation || other.activation)
        {
            if(this->activation)
            {
                if(other.activation)
                    return this->source > other.source;
                else
                    return true;
            }else{
                return false;
            }
        }

        if(this->source == -1 || other.source == -1)
        {
            if(this->source == -1)
            {
                if(other.source == -1)
                    return this->target > other.target;
                else
                    return false;
            }else{
                return true;
            }
        }

        return this->target > other.target;
    }
};

struct DisplayLabel
{
    int side;
    bool active;
    QColor color;
    DisplayLabel(int s, QColor c, bool isActive=true){side = s; color = c; active=isActive;}
    bool operator==(const DisplayLabel &other) const{
        return (side == other.side && active == other.active && color == other.color);
    }
};

// Just to clarify, the areas the lists of signals on a tile are as follows:
//
//  ___ ___ ___
// | 0 | 5 | 1 |
// |___| | |___|
// |4----+----4|
// |___  |  ___|
// | 2 | | | 3 |
// |___|_5_|___|
//
// so, area[1] would be a list of all the signals in the upper right corner.
//
// and the area weights are as follows:
//
//  0|  1|  2|
//   v   v   v
//  ___ ___ ___
// |   |   |   |  <-3
// |___|___|___|
// |   |   |   |  <-4
// |___|___|___|
// |   |   |   |  <-5
// |___|___|___|
//
// The area weights refer to what percent of the total width/height that column/row gets.
// A given area weight, say 0, gets either the average of it's two corner lists' sizes, or
// the size of the middle list.  For example, weight 0 is the average of the size of list
// 0 and 2, where as weight 1 is just the size of list 5.


class DisplayTile : public QGraphicsItem
{
private:
    QList<DisplayLabel> labels[8];
    int size;
    QList<DisplaySignal> area[6];

public:
    DisplayTile(int size=100);

    DisplayTile &operator <<(const DisplayLabel &label); // Overload to add a new Label.
    DisplayTile &operator <<(const DisplaySignal &signal); // Overload to add a new Signal

    QRectF boundingRect() const;

    void addLabel(const DisplayLabel &newLabel); //Adds a label to the correct list.
    void addSignal(const DisplaySignal &newSignal); // Adds a signal to the correct area.
    void drawOutline(QPainter &painter) const; // Draws the labels of the tile.
    void drawSignals(QPainter &painter); // Draws the signals of the tile.
    void drawTile(QPainter &painter); // Draws the whole tile.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // DISPLAYTILE_H
