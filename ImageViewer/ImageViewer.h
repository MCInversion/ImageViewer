#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "qlayoutitem.h"
#include "ui_ImageViewer.h"
#include <vector>
#include <thread>
#include <QtConcurrent/QtConcurrent>
#include <QProgressBar>
#include <QDebug>
#include <QtGui>
#include "ImageFilter.h"

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

public:
	QImage getImage(int i);
	QImage& getLast();
	void startBlurComputationThread(ImageFilter *filter);
	void startSharpenComputationThread(ImageFilter *filter);
	std::thread& getRunningThread();
protected:
	void resizeEvent(QResizeEvent *event);
private:
	Ui::ImageViewerClass ui;
	QList<QImage> images;
	QMap<QImage, ImageFilter> imageToFilter;

	int currentImgId = -1;
	int processedImgId = -1;

	// image methods
	QImage getResized(QImage *image, const QSize &newSize, bool keepAspectRatio = true);
	void replaceImageAt(QImage *replacement, int i);
	bool openImage(const QString &fileName);
	bool saveImage(const QString &fileName);
	void displayImage(QImage *image);
	void removeSelected();
	bool eventFilter(QObject* object, QEvent* event);
	void clearViewer();

	// process/thread methods
	void checkIfDone();

	// process/thread vars
	QProgressBar _bar;
	QTimer _timer;
	bool _filter_computation_started = false;
	std::thread _running_process_th;
};

