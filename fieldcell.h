#ifndef FIELDCELL_H
#define FIELDCELL_H

#include <QGraphicsRectItem>
#include <QObject>
#include <points.h>

class FieldCell : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	explicit FieldCell(qreal x, qreal y, int PosX, int PosY, bool isWall = false,qreal w = 50, qreal h = 50, QGraphicsItem *parent = nullptr);

	QString getPoint();
	void setPoint(QString str);

	bool isWall();

	int getX();
	int getY();

private:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

	void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

	void paintPoint(QPainter *painter);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

	bool isOccupiedCell();
signals:
	void sigSetStart(FieldCell *cell);
	void sigFindWay(FieldCell *cell);
	void sigDeltePath();


private:
	bool m_path = false;
	QString m_point = "";
	bool m_isWall;
	int x;
	int y;


};

#endif // FIELDCELL_H
