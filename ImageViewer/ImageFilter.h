#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <thread>
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
public:
	ImageFilter();
	ImageFilter(QString type, int radius, int amount);
	~ImageFilter();

	void setType(QString type);
	void setRadius(int radius);
	void setAmount(int amount);

	QString getType();
	int Radius();
	int Amount();

	// procedures
	void kernelSum(QImage &targetImage, QImage &resultImage, int x, int y, int ix, int jx, int iy, int jy);
	QImage getResult(QImage *targetImage);
	void applyBlur(QImage *targetImage);
	void applySharpen(QImage *targetImage);

	// threads
	std::vector<std::thread> kernelThreads;
};

#endif // IMAGEFILTER_H
