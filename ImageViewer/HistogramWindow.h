#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include "ui_HistogramWindow.h"
#include <vector>

class HistogramWindow : public QWidget
{
	Q_OBJECT

public:
	HistogramWindow(QWidget *parent = Q_NULLPTR);
	~HistogramWindow();
	void ShowHistogram(QImage targetImage);
public slots:
	void ActionReplot();
protected:
	void resizeEvent(QResizeEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	Ui::HistogramWindow ui;
	QImage *_targetImage = NULL;
	QImage *_histogramPlot = NULL;

	std::vector<int> _count_RED = std::vector<int> (256, 0);
	std::vector<int> _count_GREEN = std::vector<int> (256, 0);
	std::vector<int> _count_BLUE = std::vector<int> (256, 0);
	bool _computed = false;
	unsigned int _max_value;

	void computeHistogram(QImage *targetImage);
	void drawLine(const QPoint &startPt, const QPoint &endPt, QColor color, int width);
	QImage getResized(QImage *image, const QSize &newSize, bool keepAspectRatio);
	void displayImage(QImage *image);
};

#endif // HISTOGRAMWINDOW_H