#include "ImageFilter.h"



void ImageFilter::kernelSum(QImage *targetImage, QImage resultImage, int x, int y, int ix, int jx, int iy, int jy)
{
	int meanx = x;
	int meany = y;

	float sumR = 0.;
	float sumG = 0.;
	float sumB = 0.;
	float wsum = 0.;
	float weight;

	float sigma = radius / 2.75;

	for (int i = x - ix; i <= x + jx; i++) {
		for (int j = y - iy; j <= y + jy; j++) {
			weight = 1. / (2. * M_PI * sigma * sigma) * exp(-((meanx - i) * (meanx - i) + (meany - j) * (meany - j)) / (2. * sigma * sigma));

			sumR += targetImage->pixelColor(i, j).red() * weight;
			sumG += targetImage->pixelColor(i, j).green() * weight;
			sumB += targetImage->pixelColor(i, j).blue() * weight;

			wsum += weight;
		}
	}

	QColor resultColor = QColor(((int)((sumG / wsum) * 255 + 0.5)), ((int)((sumG / wsum) * 255 + 0.5)), ((int)((sumG / wsum) * 255 + 0.5)));
	resultImage.setPixelColor(QPoint(x, y), resultColor);
}

ImageFilter::ImageFilter()
{
}

ImageFilter::ImageFilter(QString type, int radius, int amount)
{
	this->radius = radius;
	this->type = type;
	this->amount = amount;
}


ImageFilter::~ImageFilter()
{
}

QString ImageFilter::getType()
{
	return type;
}

void ImageFilter::setType(QString type)
{
	this->type = type;
}

int ImageFilter::Radius()
{
	return radius;
}

int ImageFilter::Amount()
{
	return amount;
}

void ImageFilter::setRadius(int radius)
{
	this->radius = radius;
}

void ImageFilter::setAmount(int amount)
{
	this->amount = amount;
}

void ImageFilter::applyBlur(QImage *targetImage)
{
	if (targetImage->isNull()) {
		return;
	}	

	int x, y, ix, iy, jx, jy;

	int height = targetImage->height();
	int width = targetImage->width();

	QImage::Format format = targetImage->format();
	resultImage = QImage(width, height, format);
	resultImage.fill(QColor(0, 0, 0));

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			// kernel correction at the edges
			if (x - radius < 0) {
				ix = x;
			}
			else ix = radius;

			if (y - radius < 0) {
				iy = y;
			}
			else iy = radius;

			if (x + radius > width - 1) {
				jx = width - 1 - x;
			}
			else jx = radius;

			if (y + radius > height - 1) {
				jy = height - 1 - y;
			}
			else jy = radius;

			kernelSum(targetImage, resultImage, x, y, ix, jx, iy, jy);
		}
	}
}

void ImageFilter::applySharpen(QImage *targetImage)
{
	QImage sharpenedImage = QImage(*targetImage);
	applyBlur(targetImage);
	
	int height = targetImage->height();
	int width = targetImage->width();

	float redF, greenF, blueF;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; x++) {
			redF = ((float)sharpenedImage.pixelColor(x, y).red() + amount * (sharpenedImage.pixelColor(x, y).red() - targetImage->pixelColor(x, y).red()));
			greenF = ((float)sharpenedImage.pixelColor(x, y).green() + amount * (sharpenedImage.pixelColor(x, y).green() - targetImage->pixelColor(x, y).green()));
			blueF = ((float)sharpenedImage.pixelColor(x, y).blue() + amount * (sharpenedImage.pixelColor(x, y).blue() - targetImage->pixelColor(x, y).blue()));
			
			redF = std::max((float)0., redF);
			greenF = std::max((float)0., greenF);
			blueF = std::max((float)0., blueF);

			QColor resultColor = QColor(((int)redF + 0.5), ((int)greenF + 0.5), ((int)blueF + 0.5));
			sharpenedImage.setPixelColor(QPoint(x, y), resultColor);
		}
	}
	*targetImage = sharpenedImage;
}

QImage ImageFilter::getResult(QImage *targetImage)
{
	if (resultImage.isNull()) {
		if (type == "blur") {
			applyBlur(targetImage);
		}
		else if (type == "sharpen") {
			applySharpen(targetImage);
		}
	}
	return resultImage;
}
