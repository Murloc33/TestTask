#include <QRandomGenerator>
#include <QSharedPointer>
#include <QQueue>
#include <QVector>
#include <QMessageBox>
#include <QtAlgorithms>

#include "points.h"
#include "fieldcell.h"
#include "field.h"


void Field::updateField()
{
	Points::Instance().update();

	m_start = nullptr;

	for (QVector<FieldCell *> &vec : m_field) {
		qDeleteAll(vec.begin(), vec.end());
	}

	m_field.clear();
	m_field.reserve(m_width);

	slotDeletePath();
}

void Field::freeTree(Node *tree)
{
	if (!tree->childs.empty()) {
		for (auto child : tree->childs) {
			freeTree(child);
		}
	}
	delete tree;
}

Field::Field(QGraphicsScene *scene)
	: m_scene(scene)
{
}

Field::~Field()
{
	delete m_start;
	delete m_path;
	delete m_pathItem;
	delete m_scene;
}


void Field::generateField()
{
	updateField();

	for (int x = 0; x < m_width; ++x) {
		QVector<FieldCell *> curVector;
		curVector.reserve(m_height);

		for (int y = 0; y < m_height; ++y) {
			FieldCell *square = new FieldCell(
				x * 50, y * 50, x, y, QRandomGenerator::global()->bounded(-1, 1)
			);

			connect(square, &FieldCell::sigSetStart, this, &Field::slotSetStart);
			connect(square, &FieldCell::sigFindWay, this, &Field::slotFindWay);
			connect(square, &FieldCell::sigDeltePath, this, &Field::slotDeletePath);

			m_scene->addItem(square);

			curVector.push_back(square);
		}

		m_field.push_back(curVector);
	}
}

void Field::updateSizeField(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Field::slotFindWay(FieldCell * end)
{
	QQueue<Field::Node *> queue;
	QVector<FieldCell *> visited;

	Field::Node *start = new Field::Node();
	start->parent = nullptr;
	start->value = m_start;

	visited.push_back(start->value);
	queue.push_back(start);

	while (!queue.empty()) {
		Field::Node *currentCell = queue.front();
		queue.pop_front();

		if (currentCell->value->isWall()) {
			continue;
		}

		if (currentCell->value == end) {
			m_path = currentCell;
			generatePath();
			freeTree(start);
			return;
		}

		int currentNodeX = currentCell->value->getX();
		int currentNodeY = currentCell->value->getY();

		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				if ((x != 0 && y != 0) || (x == y)) {
					continue;
				}

				int newPosX = currentNodeX + x;
				int newPosY = currentNodeY + y;

				if ((newPosX < 0 || newPosY < 0)
					|| newPosX >= m_field.size()
					|| newPosY >= m_field[newPosX].size()) {
					continue;
				}

				if (!visited.contains(m_field[newPosX][newPosY])) {
					visited.append(m_field[newPosX][newPosY]);

					Field::Node *newNode = new Field::Node();
					newNode->value = m_field[newPosX][newPosY];
					newNode->parent = currentCell;
					currentCell->childs.append(newNode);

					queue.push_back(newNode);
				}
			}
		}
	}
}

void Field::slotDeletePath()
{
	if (m_pathItem && m_pathItem->isActive()) {
		m_scene->removeItem(m_pathItem);
		m_pathItem = nullptr;
	}

}

void Field::generatePath()
{

	QPainterPath painterPath(m_path->value->boundingRect().center());

	while(m_path->parent) {
		m_path = m_path->parent;
		painterPath.lineTo(m_path->value->boundingRect().center());
	}

	QGraphicsPathItem *pathItem = new QGraphicsPathItem(painterPath);
	pathItem->setPen(QPen(Qt::black, 2));

	m_scene->addItem(pathItem);

	m_pathItem = pathItem;
}

QGraphicsScene *Field::getScene()
{
	return m_scene;
}

void Field::slotSetStart(FieldCell *start)
{
	m_start = start;
}

