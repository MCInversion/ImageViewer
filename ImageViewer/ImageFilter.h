#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <vector>
#include <cstdlib>

class ImageFilter
{
private:
	QString type;
	QImage *resultImage = NULL;
	float sigma = 10.;
	float amount = 10.;
public:
	ImageFilter();
	ImageFilter(QString type);
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
};

#endif // IMAGEFILTER_H
