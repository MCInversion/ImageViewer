#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "qlayoutitem.h"
#include "ui_ImageViewer.h"
#include "ImageFilter.h"
#include <vector>
#include <thread>
#include <future>
#include <QtConcurrent/QtConcurrent>
#include <QProgressBar>
#include <QFuture>
#include <QDebug>
#include <QtGui>

class FilteredImage
{
public:
	FilteredImage(QImage* original) { originalImage = original; };
	~FilteredImage() {};

	QImage* originalImage = NULL;
	QImage* processedImage = NULL;
};

class ImageViewer : public QMainWindow
{
	Q_OBJECT

public:
	ImageViewer(QWidget *parent = Q_NULLPTR);
public slots:
	void ActionOpenImage();
	void ActionLoadImage();
	void ActionSaveImage();

	void ActionChangeRadius();
	void ActionChangeAmount();

	void ActionBlur();
	void ActionSharpen();
	QImage getImage(int i);
	QImage getLast();
	void startBlurComputationThread(ImageFilter *filter);
	std::thread& getRunningThread();
protected:
	void resizeEvent(QResizeEvent *event);
	//void keyPressEvent(QKeyEvent *event);
private:
	Ui::ImageViewerClass ui;
	QList<FilteredImage> images;
	int currentImgId = -1;
	bool _filter_computation_started = false;

	QImage getResized(QImage *image, const QSize &newSize, bool keepAspectRatio = true);
	void replaceImageAt(std::future<QImage>& futureReplacement, int i);
	void replaceImageAt(QImage *replacement, int i);
	bool openImage(const QString &fileName);
	bool saveImage(const QString &fileName);
	void displayImage(QImage *image);
	void removeSelected();
	bool eventFilter(QObject* object, QEvent* event);
	void clearViewer();

	void checkIfDone();

	QProgressBar bar;
	QTimer timer;
	std::thread _running_process_th;
};
