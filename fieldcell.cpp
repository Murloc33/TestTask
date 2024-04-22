#include "fieldcell.h"
#include "points.h"

#include <QGraphicsTextItem>
#include <QPainter>
#include <QMessageBox>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


FieldCell::FieldCell(qreal x, qreal y, int PosX, int PosY, bool isWall,qreal w, qreal h , QGraphicsItem *parent)
	: QGraphicsRectItem(x, y, w, h, parent), m_isWall(isWall), x(PosX), y(PosY)
{
	setPen(QPen(Qt::black, 1));
	setBrush(QBrush(isWall ? Qt::black : Qt::white));
	setAcceptHoverEvents(true);
}

void FieldCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (!Points::Instance().getCountRemainingPoints() || isOccupiedCell()) {
		return;
	}

	m_point = Points::Instance().getCurrentPoint();


	if (m_point == "A") {
		emit sigSetStart(this);

	}

	update();
	event->accept();
}

void FieldCell::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	if (isOccupiedCell()) {
		return;
	}

	if (Points::Instance().isLeftOne()) {
		emit sigFindWay(this);
	}
	event->accept();
}

void FieldCell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	if (isOccupiedCell()) {
		return;
	}

	if (Points::Instance().isLeftOne()) {
		emit sigDeltePath();
	}
	event->accept();
}

void FieldCell::paintPoint(QPainter *painter)
{
	if (m_point.isEmpty()) {
		return;
	}

	painter->drawText(rect(), Qt::AlignCenter, m_point);
}


void FieldCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QGraphicsRectItem::paint(painter, option, widget);
	paintPoint(painter);
}

bool FieldCell::isOccupiedCell()
{
	return m_point == "A" || m_isWall;
}

QString FieldCell::getPoint()
{
	return m_point;
}

void FieldCell::setPoint(QString str)
{
	m_point = str;
	update();
}


bool FieldCell::isWall()
{
	return m_isWall;
}


int FieldCell::getX() {
	return x;
}


int FieldCell::getY()
{
	return y;
}
