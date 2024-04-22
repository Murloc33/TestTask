#ifndef FIELDQGRAPHICSVIEW_H
#define FIELDQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMatrix>

class FieldQGraphicsView : public QGraphicsView {
	Q_OBJECT

public:
	FieldQGraphicsView(QWidget *parent = nullptr);

protected:
	void wheelEvent(QWheelEvent *event) override;

private:
	void zoomIn();

	void zoomOut();
};
#endif // FIELDQGRAPHICSVIEW_H
