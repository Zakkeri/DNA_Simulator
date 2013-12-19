#include "displaytile.h"
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
        area[4].append(newSignal);
    else if((newSignal.source == 1 && newSignal.target == 3) ||
            (newSignal.source == 3 && newSignal.target == 1))
        area[5].append(newSignal);
    else if(newSignal.source == -1)
    {
        if(newSignal.target % 2)
            area[5].append(newSignal);
        else
            area[4].append(newSignal);
    }
}

void DisplayTile::drawOutline(QPainter &painter) const
{
    QPen tilePen;
    QVector<qreal> dashPattern;

    tilePen.setWidth(this->size / 100);
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
    QPoint arrowPoints[3];
    QPoint start, end;
    QPen tilePen, arrowPen;
    QBrush arrowBrush;
    QVector<qreal> dashPattern;
    dashPattern << 2 << 5;
    arrowPen.setStyle(Qt::SolidLine);
    arrowBrush.setStyle(Qt::SolidPattern);

    tilePen.setWidth(this->size / 200);

    areaWeight[0] = area[0].size() / 2.0 + area[2].size() / 2.0 + 1.0;
    areaWeight[1] = area[5].size() + 1.0;
    areaWeight[2] = area[1].size() / 2.0 + area[3].size() / 2.0 + 1.0;
    areaWeight[3] = area[0].size() / 2.0 + area[1].size() / 2.0 + 1.0;
    areaWeight[4] = area[4].size() + 1.0;
    areaWeight[5] = area[2].size() / 2.0 + area[3].size() / 2.0 + 1.0;

    currentHalfTotal = areaWeight[0] + areaWeight[1] + areaWeight[2] + 3;
    areaWeight[0] /= currentHalfTotal;
    areaWeight[1] /= currentHalfTotal;
    areaWeight[2] /= currentHalfTotal;
    currentHalfTotal = areaWeight[3] + areaWeight[4] + areaWeight[5] + 1;
    areaWeight[3] /= currentHalfTotal;
    areaWeight[4] /= currentHalfTotal;
    areaWeight[5] /= currentHalfTotal;

    for(int i = 0; i < 6; i++)
    {
        if(area[i].empty())
            continue;

        qSort(area[i]);

        float xInc;
        float yInc;

        switch(i)
        {
        case 0:
            xInc = areaWeight[0] * size / (area[i].size());
            yInc = areaWeight[3] * size / (area[i].size());
            start = end = QPoint(-50,-50);
            break;
        case 1:
            xInc = areaWeight[2] * size / (area[i].size());
            yInc = areaWeight[3] * size / (area[i].size());
            start = end = QPoint(50, -50);
            xInc *= -1;
            break;
        case 2:
            xInc = areaWeight[0] * size / (area[i].size());
            yInc = areaWeight[5] * size / (area[i].size());
            start = end = QPoint(-50, 50);
            yInc *= -1;
            break;
        case 3:
            xInc = areaWeight[2] * size / (area[i].size());
            yInc = areaWeight[5] * size / (area[i].size());
            start = end = QPoint(50, 50);
            xInc *= -1;
            yInc *= -1;
            break;
        case 4:
            xInc = 0;
            yInc = areaWeight[4] * size / (area[i].size());
            start = QPoint(-50, -50 + areaWeight[3] * size);
            end = start + QPoint(size, 0);
            break;
        case 5:
            xInc = areaWeight[1] * size / (area[i].size());
            yInc = 0;
            start = QPoint(-50 + areaWeight[0] * size, 50);
            end = start + QPoint(0, size);
            break;
        }

        for(QList<DisplaySignal>::iterator next = area[i].begin();
            next != area[i].end(); next++)
        {
            tilePen.setColor((*next).color);
            arrowBrush.setColor((*next).color);
            arrowPen.setColor((*next).color);
            painter.setBrush(arrowBrush);
            if((*next).activation)
            {
                tilePen.setDashPattern(dashPattern);
            }else{
                tilePen.setStyle(Qt::SolidLine);
            }

            painter.setPen(arrowPen);
            if(i < 4)
            {
                start.rx() += xInc;
                end.ry() += yInc;
                QPoint mid(start.x(), end.y());
                if((*next).target % 2)
                {
                    arrowPoints[0] = start;
                    arrowPoints[1] = start + QPoint(3, yInc / abs(yInc) * 8);
                    arrowPoints[2] = start + QPoint(-3, yInc / abs(yInc) * 8);
                    painter.drawPolygon(arrowPoints, 3);
                }else{
                    arrowPoints[0] = end;
                    arrowPoints[1] = end + QPoint(xInc / abs(xInc) * 8, 3);
                    arrowPoints[2] = end + QPoint(xInc / abs(xInc) * 8, -3);
                    painter.drawPolygon(arrowPoints, 3);
                }

                painter.setPen(tilePen);
                painter.drawLine(start, mid);
                painter.drawLine(mid, end);
            }else{
                bool init = (*next).source == -1;
                const int rSize = 6;
                const int rSize2 = rSize / 2;

                start += QPoint(xInc, yInc);
                end += QPoint(xInc, yInc);

                QPoint realStart = start;
                QPoint realEnd = end;


                if((*next).target == 0)
                {
                    if(init)
                    {
                        realStart.rx() += (areaWeight[0] + areaWeight[1] + areaWeight[2] / 2.0) * size;
                        painter.drawRect(realStart.x() - rSize2, realStart.y() - rSize2, rSize, rSize);
                    }
                    arrowPoints[0] = end;
                    arrowPoints[1] = end + QPoint(-8, 3);
                    arrowPoints[2] = end + QPoint(-8, -3);
                }else if((*next).target == 1)
                {
                    if(init)
                    {
                        realStart.ry() += (areaWeight[3] + areaWeight[4] + areaWeight[5] / 2.0) * size;
                        painter.drawRect(realStart.x() - rSize2, realStart.y() - rSize2, rSize, rSize);
                    }
                    arrowPoints[0] = end;
                    arrowPoints[1] = end + QPoint(3, -8);
                    arrowPoints[2] = end + QPoint(-3, -8);
                }else if((*next).target == 2)
                {
                    if(init)
                    {
                        realEnd.rx() -= (areaWeight[0] / 2.0 + areaWeight[1] + areaWeight[2]) * size;
                        painter.drawRect(realEnd.x() - rSize2, realEnd.y() - rSize2, rSize, rSize);
                    }
                    arrowPoints[0] = start;
                    arrowPoints[1] = start + QPoint(8, 3);
                    arrowPoints[2] = start + QPoint(8, -3);
                }else if((*next).target == 3)
                {
                    if(init)
                    {
                        realEnd.ry() -= (areaWeight[3] / 2.0 + areaWeight[4] + areaWeight[5]) * size;
                        painter.drawRect(realEnd.x() - rSize2, realEnd.y() - rSize2, rSize, rSize);
                    }
                    arrowPoints[0] = start;
                    arrowPoints[1] = start + QPoint(3, 8);
                    arrowPoints[2] = start + QPoint(-3, 8);
                }

                painter.drawPolygon(arrowPoints, 3);
                painter.setPen(tilePen);
                painter.drawLine(realStart,realEnd);
            }
        }
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

