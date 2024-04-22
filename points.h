#ifndef POINTS_H
#define POINTS_H

#include <QStack>
#include <QString>

class Points
{
	Points() = default;

public:
	static Points &Instance();

	int getCountRemainingPoints();

	QString getCurrentPoint();

	void update();

	bool isLeftOne();

private:
	QStack<QString> m_points;
};

#endif // POINTS_H
