#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "field.h"

#include <QMainWindow>
#include <qgraphicsscene.h>
#include <QGraphicsRectItem>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	void closeEvent(QCloseEvent* event);

public slots:
	void drowField();

private:
	Ui::MainWindow *ui;
	Field* m_field;
};
#endif // MAINWINDOW_H
