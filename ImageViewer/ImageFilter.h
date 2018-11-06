#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#define _USE_MATH_DEFINES
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <QtConcurrent/QtConcurrent>
#include "ImageViewer.h"

class ImageFilter
{
private:
	QString _type;
	QImage* _blurredImage = NULL;
	QImage* _sharpenedImage = NULL;
	QImage* _originalImage = NULL;
	int _radius = 10;
	int _amount = 10;
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
