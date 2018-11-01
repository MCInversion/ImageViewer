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
#include <functional>
#include "ImageViewer.h"

class ImageFilter
{
private:
	QString type;
	QImage resultImage;
	QImage originalImage;
	int radius = 10;
	int amount = 10;
	bool finished = false;
public:
	ImageFilter();
	ImageFilter(QString type, int radius, int amount);
	~ImageFilter();

	void setType(QString type);
	void setRadius(int radius);
	void setAmount(int amount);
	void setFinished(bool value);
	bool isFinished();

	QString getType();
	int Radius();
	int Amount();

	// procedures
	void kernelSum(QImage &targetImage, QImage &resultImage, int x, int y, int ix, int jx, int iy, int jy);
	QImage getResult(QImage *targetImage);
	void applyBlur(QImage *targetImage);
	void applySharpen(QImage *targetImage);
};

#endif // IMAGEFILTER_H
