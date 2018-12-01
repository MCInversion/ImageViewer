#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QWidget>
#include "ui_HistogramWindow.h"

class HistogramWindow : public QWidget
{
	Q_OBJECT

public:
	HistogramWindow(QWidget *parent = Q_NULLPTR);
	~HistogramWindow();

private:
	Ui::HistogramWindow ui;
};

#endif // HISTOGRAMWINDOW_H