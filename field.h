#ifndef FIELD_H
#define FIELD_H

#include "fieldcell.h"

#include <QObject>
#include <QStack>
#include <QString>
#include <qgraphicsscene.h>

class Field : public QObject
{
	Q_OBJECT


public:
	Field(QGraphicsScene *scene);
	~Field();

	void generateField();
	void generatePath();

	void updateSizeField(int wight, int height);
	QGraphicsScene *getScene();


public slots:
	void slotSetStart(FieldCell *start);
	void slotFindWay(FieldCell * end);
	void slotDeletePath();

public:
	struct Node
	{
		Field::Node * parent;
		FieldCell * value;
		QVector<Field::Node *> childs;
	};


private:
	void updateField();
	void freeTree(Node* tree);


private:
	QVector<QVector<FieldCell*>> m_field;

	FieldCell *m_start;
	Field::Node *m_path;

	QGraphicsPathItem *m_pathItem;
	QGraphicsScene *m_scene;

	int m_width = 0;
	int m_height = 0;
};

#endif // FIELD_H
