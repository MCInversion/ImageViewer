#include "ImageFilter.h"

QRgb ImageFilter::kernelSum(int x, int y)
{
	int meanx = x;
	int meany = y;
	int ix, iy, jx, jy;

	int height = originalImage->height();
	int width = originalImage->width();

	float sumR = 0.;
	float sumG = 0.;
	float sumB = 0.;
	float wsum = 0.;
	float weight;

	float sigma = radius / 2.75;

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

	for (int i = x - ix; i <= x + jx; i++) {
		for (int j = y - iy; j <= y + jy; j++) {
			weight = 1. / (2. * M_PI * sigma * sigma) * exp(-((meanx - i) * (meanx - i) + (meany - j) * (meany - j)) / (2. * sigma * sigma));

			sumR += originalImage->pixelColor(i, j).red() / 255. * weight;
			sumG += originalImage->pixelColor(i, j).green() / 255. * weight;
			sumB += originalImage->pixelColor(i, j).blue() / 255. * weight;

			wsum += weight;
		}
	}

	int red = std::min(((int)((sumR / wsum) * 255 + 0.5)), 255);
	int green = std::min(((int)((sumG / wsum) * 255 + 0.5)), 255);
	int blue = std::min(((int)((sumB / wsum) * 255 + 0.5)), 255);

	return QColor(red, green, blue).rgb();
}

QImage& ImageFilter::getBlurredImg()
{
	return *blurredImage;
}

QImage& ImageFilter::getSharpenedImg()
{
	return *sharpenedImage;
}

ImageFilter::ImageFilter()
{
}

ImageFilter::ImageFilter(QString type, int radius, int amount, QImage* original)
{
	this->radius = radius;
	this->type = type;
	this->amount = amount;
	this->originalImage = original;
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

void ImageFilter::applyBlur()
{
	if (originalImage->isNull()) {
		return;
	}

	int height = originalImage->height();
	int width = originalImage->width();
	QImage::Format format = originalImage->format();

	blurredImage = new QImage(width, height, format);

	int threadCount = QThreadPool::globalInstance()->maxThreadCount();
	std::cout << "child thread " << std::this_thread::get_id() << ": initiating image processing on " << threadCount << " additional threads..." << std::endl;
	int step = originalImage->height() / threadCount;

	for (int i = 0; i < threadCount; i++) {
		std::lock_guard<std::mutex> guard(_threadMutex);
		if (i + 1 < threadCount) {
			QtConcurrent::run(this, &ImageFilter::applyBlur, i * step, (i + 1) * step);
			std::cout << "child thread " << std::this_thread::get_id() << ": y from " << i * step << " to " << (i + 1) * step << std::endl;
		}
		else {
			QtConcurrent::run(this, &ImageFilter::applyBlur, i * step, originalImage->height());
			std::cout << "child thread " << std::this_thread::get_id() << ": y from " << i * step << " to " << originalImage->height() << std::endl;
		}
	}
	std::cout << "..." << std::endl;
}



void ImageFilter::applyBlur(int from, int to)
{
	QRgb col;
	for (int y = from; y < to; y++) {
		for (int x = 0; x < originalImage->width(); x++) {
			std::lock_guard<std::mutex> guard(_kernelMutex);
			col = kernelSum(x, y);
			*((QRgb*)blurredImage->scanLine(y) + x) = col;
		}		
	}
}

void ImageFilter::applySharpen()
{
	if (amount > 0) {
		applyBlur();
	
		int height = blurredImage->height();
		int width = blurredImage->width();
		QImage::Format format = blurredImage->format();

		sharpenedImage = new QImage(width, height, format);

		float redF, greenF, blueF;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				redF = ((float)(originalImage->pixelColor(x, y).red() + amount * (originalImage->pixelColor(x, y).red() - blurredImage->pixelColor(x, y).red())));
				greenF = ((float)(originalImage->pixelColor(x, y).green() + amount * (originalImage->pixelColor(x, y).green() - blurredImage->pixelColor(x, y).green())));
				blueF = ((float)(originalImage->pixelColor(x, y).blue() + amount * (originalImage->pixelColor(x, y).blue() - blurredImage->pixelColor(x, y).blue())));
			
				redF = std::max((float)0., std::min(redF, (float)255.));
				greenF = std::max((float)0., std::min(greenF, (float)255.));
				blueF = std::max((float)0., std::min(blueF, (float)255.));

				QColor resultColor = QColor(((int)redF + 0.5), ((int)greenF + 0.5), ((int)blueF + 0.5));
				sharpenedImage->setPixelColor(QPoint(x, y), resultColor);
			}
		}
	}
}
