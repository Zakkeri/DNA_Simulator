#include "../Headers/displaytile2.h"
#include <QDebug>

void drawSquare(QPainter *p);

DisplayTile::DisplayTile(int size)
{
    this->size = size;
}

QRectF DisplayTile::boundingRect() const
{
    return QRectF(-55,-55,110,110);
}

/*DisplayTile::DisplayTile(const DisplayTile &copy)
{
    for(int i = 0; i < 8; i++)
    {
        this->labels[i] = copy.labels[i];
    }
    this->size = copy.size;
    for(int i = 0; i < 6; i++)
    {
        this->area[i] = copy.area[i];
    }
}*/

void DisplayTile::addLabel(const DisplayLabel &newLabel)
{
    if(newLabel.active)
    {
        if(0 <= newLabel.side && newLabel.side < 5)
        {
            if(!labels[newLabel.side].contains(newLabel))
                labels[newLabel.side].push_back(newLabel);
        }
    }else{
        if(0 <= newLabel.side && newLabel.side < 5)
        {
            if(!labels[newLabel.side].contains(newLabel))
                labels[newLabel.side + 4].push_back(newLabel);
        }
    }
}

void DisplayTile::addSignal(const DisplaySignal &newSignal)
{
    if((newSignal.source == 2 && newSignal.target == 3) ||
            (newSignal.source == 3 && newSignal.target == 2))
        area[0].append(newSignal);
    else if((newSignal.source == 0 && newSignal.target == 3) ||
            (newSignal.source == 3 && newSignal.target == 0))
        area[1].append(newSignal);
    else if((newSignal.source == 1 && newSignal.target == 2) ||
            (newSignal.source == 2 && newSignal.target == 1))
        area[2].append(newSignal);
    else if((newSignal.source == 0 && newSignal.target == 1) ||
            (newSignal.source == 1 && newSignal.target == 0))
        area[3].append(newSignal);
    else if((newSignal.source == 0 && newSignal.target == 2) ||
            (newSignal.source == 2 && newSignal.target == 0))
        area[5].append(newSignal);
    else if((newSignal.source == 1 && newSignal.target == 3) ||
            (newSignal.source == 3 && newSignal.target == 1))
        area[4].append(newSignal);
    else if(newSignal.source == -1)
    {
        if(newSignal.target % 2)
            area[4].append(newSignal);
        else
            area[5].append(newSignal);
    }
}

void DisplayTile::drawArrow(QPainter &painter, int startX, int startY, int endX, int endY, bool xFirst) const
{
    QPainterPath path, arrowPath;
    const QBrush startBrush = painter.brush();
    int dir;
    QPainterPathStroker stroker; //to make arrows bigger
    stroker.setWidth(this->size / 50);

    painter.setBrush(Qt::NoBrush);
    path.moveTo(startX, startY);

    if(xFirst)
    {
        path.lineTo(endX, startY);
        path.lineTo(endX, endY);
        if(startY < endY)
            dir = 1;
        else if(endY < startY)
            dir = 3;
        else if(startX < endX)
            dir = 0;
        else
            dir = 2;
    }else{
        path.lineTo(startX, endY);
        path.lineTo(endX, endY);
        if(startX < endX)
            dir = 0;
        else if(endX < startX)
            dir = 2;
        else if(startY < endY)
            dir = 1;
        else
            dir = 3;
    }
    painter.drawPath(path);

    painter.setPen(painter.pen().color());
    painter.setBrush(startBrush);

    arrowPath.moveTo(endX, endY);

    switch(dir)
    {
    case 0:
        arrowPath.lineTo(endX - 6, endY - 3);
        arrowPath.lineTo(endX - 6, endY + 3);
        arrowPath.lineTo(endX, endY);
        break;
    case 1:
        arrowPath.lineTo(endX - 3, endY - 6);
        arrowPath.lineTo(endX + 3, endY - 6);
        arrowPath.lineTo(endX, endY);
        break;
    case 2:
        arrowPath.lineTo(endX + 6, endY - 3);
        arrowPath.lineTo(endX + 6, endY + 3);
        arrowPath.lineTo(endX, endY);
        break;
    case 3:
        arrowPath.lineTo(endX - 3, endY + 6);
        arrowPath.lineTo(endX + 3, endY + 6);
        arrowPath.lineTo(endX, endY);
        break;
    }

    const QPainterPath stroked = stroker.createStroke(arrowPath);
    arrowPath = stroked.united(arrowPath);
    painter.drawPath(arrowPath);
}

void DisplayTile::drawOutline(QPainter &painter) const
{
    QPen tilePen;
    QVector<qreal> dashPattern;

    tilePen.setWidth(this->size / 50);
    dashPattern << 2 << 7;

    for(int i = 0; i < 8; i++)
    {

        if(labels[i].empty())
            continue;

        Qt::PenStyle lineType;

        int startX = -50;
        int startY = -50;
        int xInc = 0;
        int yInc = 0;

        switch(i)
        {
        case 0:
        case 4:
            startX = 50;
            yInc = (float)size / labels[i].size();
            break;
        case 1:
        case 5:
            startY = 50;

            xInc = (float)size / labels[i].size();
            break;
        case 2:
        case 6:
            startX = -50;
            yInc = (float)size / labels[i].size();
            break;
        case 3:
        case 7:
            startY = -50;
            xInc = (float)size / labels[i].size();
            break;
        }

        if(i < 4)
            lineType = Qt::SolidLine;
        else
        {
            lineType = Qt::CustomDashLine;
            tilePen.setDashPattern(dashPattern);
            if(startX > -50)
                startX -= size * .02;
            else
                startX += size * .02;
            if(startY > -50)
                startY -= size * .02;
            else
                startY += size * .02;
            yInc *= .96;
            xInc *= .96;
        }

        for(QList<DisplayLabel>::ConstIterator next = labels[i].begin();
            next != labels[i].end();
            next++)
        {

            tilePen.setColor((*next).color);
            tilePen.setStyle(lineType);
            painter.setPen(tilePen);

            painter.drawLine(startX, startY, startX + xInc, startY + yInc);

            startX += xInc;
            startY += yInc;
        }
    }
}


void DisplayTile::drawSignals(QPainter &painter)
{
    float areaWeight[6] = {0,0,0,0,0,0};
    float currentHalfTotal;
    QPen arrowPen;
    QBrush arrowBrush;
    QVector<qreal> dashPattern;
    dashPattern << 2 << 5;
    arrowPen.setStyle(Qt::SolidLine);
    arrowPen.setWidth(this->size / 50); //set width
    arrowBrush.setStyle(Qt::SolidPattern);

    areaWeight[0] = qMax(area[0].size() / 2.0 + area[2].size() / 2.0, 1.0);
    areaWeight[1] = qMax((double)area[4].size(), 1.0);
    areaWeight[2] = qMax(area[1].size() / 2.0 + area[3].size() / 2.0, 1.0);
    areaWeight[3] = qMax(area[0].size() / 2.0 + area[1].size() / 2.0, 1.0);
    areaWeight[4] = qMax((double)area[5].size(), 1.0);
    areaWeight[5] = qMax(area[2].size() / 2.0 + area[3].size() / 2.0, 1.0);

    currentHalfTotal = areaWeight[0] + areaWeight[1] + areaWeight[2] + 1.0;
    areaWeight[0] = (areaWeight[0] + 1) * 100 / currentHalfTotal;
    areaWeight[1] = (areaWeight[1] - 1) * 100 / currentHalfTotal;
    areaWeight[2] = (areaWeight[2] + 1) * 100 / currentHalfTotal;
    currentHalfTotal = areaWeight[3] + areaWeight[4] + areaWeight[5] + 1.0;
    areaWeight[3] = (areaWeight[3] + 1) * 100 / currentHalfTotal;
    areaWeight[4] = (areaWeight[4] - 1) * 100 / currentHalfTotal;
    areaWeight[5] = (areaWeight[5] + 1) * 100 / currentHalfTotal;

    for(int i = 0; i < 6; i++)
        qSort(area[i]);


    //Initialize the place variables
    float topX = -50;
    float topY = -50;
    float sideX = -50;
    float sideY = -50;
    float xInc = areaWeight[0] / (area[0].size() + 1);
    float yInc = areaWeight[3] / (area[0].size() + 1);


    // Draw area 0, between sides 2 and 3
    for(QList<DisplaySignal>::Iterator next = area[0].begin(); next != area[0].end(); next++)
    {
        arrowPen.setColor((*next).color);
        if((*next).activation)
            arrowPen.setDashPattern(dashPattern);
        else
            arrowPen.setStyle(Qt::SolidLine);

        painter.setBrush((*next).color);
        painter.setPen(arrowPen);
        topX += xInc;
        sideY += yInc;
        if((*next).target == 2)
        {
            drawArrow(painter, topX, topY, sideX, sideY, false);
        }else{
            drawArrow(painter, sideX, sideY, topX, topY);
        }
    }

    // Change place variables for area 1
    topX = 50;
    topY = -50;
    sideX = 50;
    sideY = -50;
    xInc = areaWeight[2] / (area[1].size() + 1);
    yInc = areaWeight[3] / (area[1].size() + 1);

    // Draw area 1, between sides 0 and 3
    for(QList<DisplaySignal>::Iterator next = area[1].begin(); next != area[1].end(); next++)
    {
        arrowPen.setColor((*next).color);
        if((*next).activation)
            arrowPen.setDashPattern(dashPattern);
        else
            arrowPen.setStyle(Qt::SolidLine);

        painter.setBrush((*next).color);
        painter.setPen(arrowPen);
        topX -= xInc;
        sideY += yInc;
        if((*next).target == 0)
        {
            drawArrow(painter, topX, topY, sideX, sideY, false);
        }else{
            drawArrow(painter, sideX, sideY, topX, topY);
        }
    }

    // Change place variables for area 2
    topX = -50;
    topY = 50;
    sideX = -50;
    sideY = 50;
    xInc = areaWeight[0] / (area[2].size() + 1);
    yInc = areaWeight[5] / (area[2].size() + 1);

    // Draw area 2, between sides 2 and 1
    for(QList<DisplaySignal>::Iterator next = area[2].begin(); next != area[2].end(); next++)
    {
        arrowPen.setColor((*next).color);
        if((*next).activation)
            arrowPen.setDashPattern(dashPattern);
        else
            arrowPen.setStyle(Qt::SolidLine);

        painter.setBrush((*next).color);
        painter.setPen(arrowPen);
        topX += xInc;
        sideY -= yInc;
        if((*next).target == 2)
        {
            drawArrow(painter, topX, topY, sideX, sideY, false);
        }else{
            drawArrow(painter, sideX, sideY, topX, topY);
        }
    }

    // Change place variables for area 3
    topX = 50;
    topY = 50;
    sideX = 50;
    sideY = 50;
    xInc = areaWeight[2] / (area[3].size() + 1);
    yInc = areaWeight[5] / (area[3].size() + 1);

    // Draw area 3, between sides 0 and 1
    for(QList<DisplaySignal>::Iterator next = area[3].begin(); next != area[3].end(); next++)
    {
        arrowPen.setColor((*next).color);
        if((*next).activation)
            arrowPen.setDashPattern(dashPattern);
        else
            arrowPen.setStyle(Qt::SolidLine);

        painter.setBrush((*next).color);
        painter.setPen(arrowPen);
        topX -= xInc;
        sideY -= yInc;
        if((*next).target == 0)
        {
            drawArrow(painter, topX, topY, sideX, sideY, false);
        }else{
            drawArrow(painter, sideX, sideY, topX, topY);
        }
    }

    // Change place variables for area 4
    topX = areaWeight[0] - 50;
    sideY = -50;
    topY = 50;

    if(area[4].size() == 1)
        xInc = 0;
    else
        xInc = areaWeight[1] / (area[4].size() - 1);

    // Draw area 4, between sides 1 and 3
    for(QList<DisplaySignal>::Iterator next = area[4].begin(); next != area[4].end(); next++)
    {
        arrowPen.setColor((*next).color);
        if((*next).activation)
            arrowPen.setDashPattern(dashPattern);
        else
            arrowPen.setStyle(Qt::SolidLine);

        painter.setBrush((*next).color);
        painter.setPen(arrowPen);

        if((*next).source == -1)
        {
            sideY = -50;
            topY = 50;
            if((*next).target == 1)
            {
                sideY = 50 - .5 * areaWeight[3];
                painter.drawRect(topX - 2, sideY - 2, 4, 4);
            }else{
                topY = .5 * areaWeight[5] - 50;
                painter.drawRect(topX - 2, topY - 2, 4, 4);
            }
        }

        if((*next).target == 3)
            drawArrow(painter, topX, topY, topX, sideY);
        else
            drawArrow(painter, topX, sideY, topX, topY);

        topX += xInc;
    }

    // Change place variables for area 5
    sideY = areaWeight[3] - 50;
    sideX = -50;
    topX = 50;

    if(area[5].size() == 1)
        yInc = 0;
    else
        yInc = areaWeight[4] / (area[5].size() - 1);

    // Draw area 5, between sides 2 and 0
    for(QList<DisplaySignal>::Iterator next = area[5].begin(); next != area[5].end(); next++)
    {
        arrowPen.setColor((*next).color);
        if((*next).activation)
            arrowPen.setDashPattern(dashPattern);
        else
            arrowPen.setStyle(Qt::SolidLine);

        painter.setBrush((*next).color);
        painter.setPen(arrowPen);

        if((*next).source == -1)
        {
            sideX = -50;
            topX = 50;
            if((*next).target == 0)
            {
                sideX = 50 - .5 * areaWeight[2];
                painter.drawRect(sideX - 2, sideY - 2, 4, 4);
            }else{
                topX = .5 * areaWeight[0] - 50;
                painter.drawRect(topX - 2, sideY - 2, 4, 4);
            }
        }

        if((*next).target == 0)
            drawArrow(painter, sideX, sideY, topX, sideY);
        else
            drawArrow(painter, topX, sideY, sideX, sideY);
        sideY += yInc;
    }
}

void DisplayTile::drawTile(QPainter &painter)
{
    this->drawOutline(painter);
    this->drawSignals(painter);
}

void DisplayTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*const QPoint UL(-50,-50), UR(50,-50), LL(-50,50), LR(50,50);
    QPainterPath path;
    painter->setPen(Qt::black);

    path.moveTo(UL);
    path.lineTo(UR);
    path.lineTo(LR);
    path.lineTo(LL);
    path.lineTo(UL);


    painter->drawPath(path);*/

    //drawSquare(painter);

    this->drawOutline(*painter);
    this->drawSignals(*painter);
}

void drawSquare(QPainter *p)
{
    p->setPen(Qt::black);
    p->drawRect(-50,-50,100,100);
}

DisplayTile &DisplayTile::operator <<(const DisplayLabel &label)
{
    this->addLabel(label);
    return *this;
}

DisplayTile &DisplayTile::operator <<(const DisplaySignal &signal)
{
    this->addSignal(signal);
    return *this;
}

