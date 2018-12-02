#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QProgressBar>
#include <QThread>
#include "ui_HistogramWindow.h"
#include <vector>

class Histogram : public QObject
{
	Q_OBJECT
private:
	QImage *_targetImage = NULL;
	QImage *_histogramPlot = NULL;

	bool _show_RED = true;
	bool _show_GREEN = true;
	bool _show_BLUE = true;

	std::vector<int> _count_RED = std::vector<int>(256, 0);
	std::vector<int> _count_GREEN = std::vector<int>(256, 0);
	std::vector<int> _count_BLUE = std::vector<int>(256, 0);
	bool _computed = false;
	unsigned int _max_value;

	void computeHistogram();
	void drawLine(const QPoint &startPt, const QPoint &endPt, QColor color, int width);
public:
	Histogram();
	Histogram(QImage *targetImage);
	~Histogram();
	QImage getHistogramPlot();
	bool isPlotted();

	void RED_setEnabled(bool value);
	void GREEN_setEnabled(bool value);
	void BLUE_setEnabled(bool value);
public slots:
	void plotHistogram();
signals:
	void histogramPlotted();
	void progressIncremented();
};

class HistogramThread : public QObject
{
	Q_OBJECT
public:
	QThread *thread;
	HistogramThread(QObject* parent = Q_NULLPTR);
	~HistogramThread();
};

class HistogramWindow : public QWidget
{
	Q_OBJECT

public:
	HistogramWindow(QWidget *parent = Q_NULLPTR);
	~HistogramWindow();
	void initThread(QImage targetImage);
	void initReplotThread();
signals:
	void histogramLaunched();
public slots:
	void ActionReplot();
	void actionsAfterCompletion();
protected:
	void resizeEvent(QResizeEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	Ui::HistogramWindow ui;

	Histogram *_histogram = NULL;
	HistogramThread *_computed_hist_thread = NULL;
	QProgressBar *_progressBar = NULL;

	QImage getResized(QImage *image, const QSize &newSize, bool keepAspectRatio);
	void displayImage(QImage *image);
};

#endif // HISTOGRAMWINDOW_H