#include "points.h"



Points &Points::Instance()
{
	static Points points = Points();
	return points;
}

int Points::getCountRemainingPoints()
{
	return m_points.size();
}



QString Points::getCurrentPoint()
{
	QString point = m_points.top();
	m_points.pop();
	return point;
}

void Points::update()
{
	QStack<QString> newStack;
	newStack.push("B");
	newStack.push("A");
	m_points.swap(newStack);
}

bool Points::isLeftOne()
{
	return m_points.size() == 1;
}
