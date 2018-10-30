#include "ImageFilter.h"



ImageFilter::ImageFilter()
{
}

ImageFilter::ImageFilter(QString type)
{
	sigma = 10.;
	this->type = type;
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

QImage ImageFilter::getResult(QImage *targetImage)
{
	if (resultImage == NULL) {
		if (type == "blur") {
			applyBlur(targetImage);
		}
		else if (type == "sharpen") {
			applySharpen(targetImage);
		}
	}
	return *resultImage;
}

float ImageFilter::Sigma()
{
	return sigma;
}

float ImageFilter::Amount()
{
	return amount;
}

void ImageFilter::setSigma(float sigma)
{
	this->sigma = sigma;
}

void ImageFilter::setAmound(float amount)
{
	this->amount = amount;
}

void ImageFilter::applyBlur(QImage *targetImage)
{
	int i, j, x, y, ix, iy, jx, jy, meanx, meany;
	float sumR, sumG, sumB;
	float wsum;
	float weight;

	int height = targetImage->height();
	int width = targetImage->width();

	QImage::Format format = targetImage->format();
	*resultImage = QImage(width, height, format);

	int signifRadius = ((int) 2.75 * sigma + 0.5);

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {

			sumR = 0.0, sumG = 0.0, sumB = 0.0;
			wsum = 0.0;

			//Position correction at the edges
			if (x - signifRadius < 0) {
				ix = x;
			}
			else ix = signifRadius;

			if (y - signifRadius < 0) {
				iy = y;
			}
			else iy = signifRadius;

			if (x + signifRadius > width - 1) {
				jx = width - 1 - x;
			}
			else jx = signifRadius;

			if (y + signifRadius > height - 1) {
				jy = height - 1 - y;
			}
			else jy = signifRadius;

			meanx = x;
			meany = y;

			for (i = x - ix; i <= x + jx; i++) {
				for (j = y - iy; j <= y + jy; j++) {
					weight = 1. / (2. * M_PI * sigma * sigma) * exp(-((meanx - i) * (meanx - i) + (meany - j) * (meany - j)) / (2. * sigma * sigma));

					sumR += targetImage->pixelColor(i, j).red() * weight;
					sumG += targetImage->pixelColor(i, j).green() * weight;
					sumB += targetImage->pixelColor(i, j).blue() * weight;

					wsum += weight;
				}
			}

			QColor resultColor = QColor(((int)((sumG / wsum) * 255 + 0.5)), ((int)((sumG / wsum) * 255 + 0.5)), ((int)((sumG / wsum) * 255 + 0.5)));
			resultImage->setPixelColor(QPoint(x, y), resultColor);
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
			
			QColor resultColor = QColor(((int)redF + 0.5), ((int)greenF + 0.5), ((int)blueF + 0.5));
			sharpenedImage.setPixelColor(QPoint(x, y), resultColor);
		}
	}
	*targetImage = sharpenedImage;
}
