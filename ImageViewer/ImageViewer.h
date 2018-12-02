#pragma once

#define _USE_MATH_DEFINES
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "qlayoutitem.h"
#include "ui_ImageViewer.h"
#include "ui_HistogramWindow.h"
#include "HistogramWindow.h"
#include <vector>
#include <map>
#include <thread>
#include <QtConcurrent/QtConcurrent>
#include <QProgressBar>
#include <QMap>
#include <QFuture>
#include <QDebug>
#include <QtGui>
#include <QTimer>


class ImageFilter: public QObject
{
	Q_OBJECT
private:
	QObject *parent = 0;
	QString _type;
	QImage _blurredImage;
	QImage _sharpenedImage;
	QImage _originalImage;
	int _radius = 10;
	int _amount = 10;

	int _progress;
	int _progress_percent;
public:
	ImageFilter();
	ImageFilter(QString type, int radius, int amount, QImage original);
	~ImageFilter();

	void setType(QString type);
	void setRadius(int radius);
	void setAmount(int amount);

	QString getType();
	int Radius();
	int Amount();

	// procedures
	QRgb kernelSum(int x, int y);
	QImage getOriginalImg();
	QImage getBlurredImg();
	QImage getSharpenedImg();	
public slots:
	void applyBlur();
	void applySharpen();
signals:
	void filterComputationComplete();
	void progressIncremented();
};

class FilterThread : public QObject
{
	Q_OBJECT
public:
	QThread* thread;
	FilterThread(QObject* parent = Q_NULLPTR);
	~FilterThread();
};

class ImageViewer : public QMainWindow
{
	Q_OBJECT

public:
	ImageViewer(QWidget *parent = Q_NULLPTR);
	~ImageViewer();

	QImage getImage(int i);
	QImage& getLast();

public slots:
	void ActionOpenImage();
	void ActionLoadImage();
	void ActionSaveImage();

	void ActionChangeRadius();
	void ActionChangeAmount();

	void ActionBlur();
	void ActionSharpen();

	void actionsAfterCompletion();

	void ActionDisplayBlurred();
	void ActionDisplaySharpened();

	void interruptThread();

	void incrementProgress();

	void ActionOpenHistogram();
signals:
	void launchComputation();
protected:
	void resizeEvent(QResizeEvent *event);
	void closeEvent(QCloseEvent *event);
private:
	// windows
	Ui::ImageViewerClass ui;
	HistogramWindow *_activeHistogram;

	// Image vars
	QList<QImage> images;
	QImage _processedImage;
	ImageFilter* _activeFilter = NULL;
	// TODO: a list of active filters that can be found by keys

	int currentImgId = -1;
	int processedImgId = -1;

	QProgressBar *_progressBar = NULL;
	int _computation_progress;
	void initProgress();

	// image methods
	QImage getResized(QImage *image, const QSize &newSize, bool keepAspectRatio = true);
	void replaceImageAt(QImage replacement, int i);
	bool openImage(const QString &fileName);
	bool saveImage(const QString &fileName);
	void displayImage(QImage *image);
	void removeSelected();
	bool eventFilter(QObject* object, QEvent* event);
	void clearViewer();

	// process/thread vars
	FilterThread* _process_thread = NULL;
	bool _filter_computation_started = false;

	void startBlurComputationThread(int radius, int amount, QImage original);
	void startSharpenComputationThread(int radius, int amount, QImage original);

	void showProgress();
};