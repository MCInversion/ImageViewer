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
	QImage *resultImage = NULL;
	float sigma = 10.;
	float amount = 10.;
	void kernelSum(QImage *targetImage, QImage *resultImage, int x, int y, int ix, int jx, int iy, int jy);
public:
	ImageFilter();
	ImageFilter(QString type, float radius, float amount);
	~ImageFilter();

	void setType(QString type);
	void setSigma(float sigma);
	void setAmound(float amount);

	QString getType();
	float Sigma();
	float Amount();

	// procedures
	QImage getResult(QImage *targetImage);
	void applyBlur(QImage *targetImage);
	void applySharpen(QImage *targetImage);

	// threads
	std::vector<std::thread> kernelThreads;
};

#endif // IMAGEFILTER_H
