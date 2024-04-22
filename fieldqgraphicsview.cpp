#include "fieldqgraphicsview.h"


FieldQGraphicsView::FieldQGraphicsView(QWidget *parent): QGraphicsView(parent)
{
}

void FieldQGraphicsView::wheelEvent(QWheelEvent *event){
	if (event->angleDelta().y() > 0) {
		zoomIn();
	} else {
		zoomOut();
	}
}

void FieldQGraphicsView::zoomIn()
{
	scale(1.25, 1.25);
}

void FieldQGraphicsView::zoomOut()
{
	scale(0.8, 0.8);
}


