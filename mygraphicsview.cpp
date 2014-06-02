#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    //qDebug()<<"Wheel event with delta = "<<event->delta();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0)
    {
      // Zoom in
      scale(scaleFactor, scaleFactor);
    }
    else
    {
       // Zooming out
       scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

}
