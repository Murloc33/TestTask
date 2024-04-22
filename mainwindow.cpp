#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
#include "settings.h"

#include <QRandomGenerator>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <QRegExpValidator>
#include <QMessageBox>

#define SETTINGS_GEOMETRY "geometry"
#define SETTINGS_STATE "state"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setMouseTracking(true);

	ui->width->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->width));
	ui->height->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->height));

	m_field = new Field(new QGraphicsScene(this));

	QSettings* settings = Settings::settings();
	restoreGeometry(settings->value(SETTINGS_GEOMETRY).toByteArray());
	restoreState(settings->value(SETTINGS_STATE).toByteArray());

	QObject::connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::drowField);


}


MainWindow::~MainWindow()
{
	delete ui;
	delete m_field;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	QSettings* settings = Settings::settings();
	settings->setValue(SETTINGS_GEOMETRY, saveGeometry());
	settings->setValue(SETTINGS_STATE, saveState());

	event->accept();
}

void MainWindow::drowField()
{
	if (ui->width->text().isEmpty() || ui->height->text().isEmpty()) {
		QMessageBox::warning(this, tr("Внимание"), tr("Недопустимый размер поля"));
		return;
	}
	if (ui->width->text().toInt() > 100 || ui->height->text().toInt() > 100) {
		QMessageBox::warning(this, tr("Внимание"), tr("Недопустимый размер поля"));
		return;
	}

	m_field->updateSizeField(ui->width->text().toInt(),
							 ui->height->text().toInt());
	m_field->generateField();

	QGraphicsScene *scene = m_field->getScene();
	ui->graphicsView->setScene(scene);

	QRectF sceneRect = scene->itemsBoundingRect();
	ui->graphicsView->setSceneRect(sceneRect);
}


