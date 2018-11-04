#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <thread>
#include <future>
#include <mutex>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <functional>
#include "ImageViewer.h"

class ImageFilter
{
private:
	QString type;
	QImage* originalImage = NULL;
	QImage* blurredImage = NULL;
	QImage* sharpenedImage = NULL;
	int radius = 10;
	int amount = 10;
	bool useHardwareConcurrency = false;
	std::mutex _threadMutex;
	std::mutex _kernelMutex;
public:
	ImageFilter();
	ImageFilter(QString type, int radius, int amount, QImage* original);
	~ImageFilter();

	void setType(QString type);
	void setRadius(int radius);
	void setAmount(int amount);

	QString getType();
	int Radius();
	int Amount();

	// procedures
	QRgb kernelSum(int x, int y);
	QImage& getBlurredImg();
	QImage& getSharpenedImg();
	void applyBlur();
	void applyBlur(int from, int to);
	void applySharpen();
};

#endif // IMAGEFILTER_H
