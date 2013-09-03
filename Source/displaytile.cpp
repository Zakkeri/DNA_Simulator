#include "displaytile.h"

DisplayTile::DisplayTile()
{
    x = y = 0;
    size = 100;
}

DisplayTile::DisplayTile(int x, int y, int size)
{
    this->size = size;
    this->x = x;
    this->y = y;
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

    for(int i = 0; i < 8; i++)
    {

        if(labels[i].empty())
            continue;

        Qt::PenStyle lineType;

        int startX = x;
        int startY = y;
        int xInc = 0;
        int yInc = 0;

        switch(i)
        {
        case 0:
        case 4:
            startX = x + size;
            yInc = (float)size / labels[i].size();
            break;
        case 1:
        case 5:
            startY = y + size;
            xInc = (float)size / labels[i].size();
            break;
        case 2:
        case 6:
            yInc = (float)size / labels[i].size();
            break;
        case 3:
        case 7:
            xInc = (float)size / labels[i].size();
            break;
        }

        if(i < 4)
            lineType = Qt::SolidLine;
        else
        {
            lineType = Qt::DashLine;
            if(startX > x)
                startX -= size * .01;
            else
                startX += size * .01;
            if(startY > y)
                startY -= size * .01;
            else
                startY += size * .01;
            yInc *= .98;
            xInc *= .98;
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


void DisplayTile::drawSignals(QPainter &painter) const
{
    float areaWeight[6] = {0,0,0,0,0,0};
    float currentHalfTotal;
    QPoint arrowPoints[3];
    QPoint start, end;
    QPen tilePen;
    QBrush arrowBrush;
    arrowBrush.setStyle(Qt::SolidPattern);

    areaWeight[0] = area[0].size() / 2.0 + area[2].size() / 2.0;
    areaWeight[1] = area[5].size();
    areaWeight[2] = area[1].size() / 2.0 + area[3].size() / 2.0;
    areaWeight[3] = area[0].size() / 2.0 + area[1].size() / 2.0;
    areaWeight[4] = area[4].size();
    areaWeight[5] = area[2].size() / 2.0 + area[3].size() / 2.0;

    currentHalfTotal = areaWeight[0] + areaWeight[1] + areaWeight[2] + 1;
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

        float xInc;
        float yInc;
        switch(i)
        {
        case 0:
            xInc = areaWeight[0] * size / (area[i].size());
            yInc = areaWeight[3] * size / (area[i].size());
            start = end = QPoint(x,y);
            break;
        case 1:
            xInc = areaWeight[2] * size / (area[i].size());
            yInc = areaWeight[3] * size / (area[i].size());
            start = end = QPoint(x + size, y);
            xInc *= -1;
            break;
        case 2:
            xInc = areaWeight[0] * size / (area[i].size());
            yInc = areaWeight[5] * size / (area[i].size());
            start = end = QPoint(x, y + size);
            yInc *= -1;
            break;
        case 3:
            xInc = areaWeight[2] * size / (area[i].size());
            yInc = areaWeight[5] * size / (area[i].size());
            start = end = QPoint(x + size, y + size);
            xInc *= -1;
            yInc *= -1;
            break;
        case 4:
            xInc = 0;
            yInc = areaWeight[4] * size / (area[i].size());
            start = QPoint(x, y + areaWeight[3] * size);
            end = start + QPoint(size, 0);
            break;
        case 5:
            xInc = areaWeight[1] * size / (area[i].size());
            yInc = 0;
            start = QPoint(x + areaWeight[0] * size, y);
            end = start + QPoint(0, size);
            break;
        }

        for(QList<DisplaySignal>::ConstIterator next = area[i].begin();
            next != area[i].end(); next++)
        {
            tilePen.setColor((*next).color);
            arrowBrush.setColor((*next).color);
            painter.setBrush(arrowBrush);

            if((*next).activation)
                tilePen.setStyle(Qt::DashLine);
            else
                tilePen.setStyle(Qt::SolidLine);

            painter.setPen(tilePen);
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
                painter.drawLine(realStart,realEnd);
            }
        }
    }
}

void DisplayTile::drawTile(QPainter &painter) const
{
    this->drawOutline(painter);
    this->drawSignals(painter);
}

void DisplayTile::moveTile(int newX, int newY)
{
    this->x = newX;
    this->y = newY;
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
