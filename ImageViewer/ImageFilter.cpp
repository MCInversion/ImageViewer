#include "ImageFilter.h"

QRgb ImageFilter::kernelSum(int x, int y)
{
	int meanx = x;
	int meany = y;
	int ix, iy, jx, jy;

	int height = _originalImage->height();
	int width = _originalImage->width();

	float sumR = 0.;
	float sumG = 0.;
	float sumB = 0.;
	float wsum = 0.;
	float weight;

	float sigma = _radius / 2.75;

	if (x - _radius < 0) {
		ix = x;
	}
	else ix = _radius;

	if (y - _radius < 0) {
		iy = y;
	}
	else iy = _radius;

	if (x + _radius > width - 1) {
		jx = width - 1 - x;
	}
	else jx = _radius;

	if (y + _radius > height - 1) {
		jy = height - 1 - y;
	}
	else jy = _radius;

	for (int i = x - ix; i <= x + jx; i++) {
		for (int j = y - iy; j <= y + jy; j++) {
			weight = 1. / (2. * M_PI * sigma * sigma) * exp(-((meanx - i) * (meanx - i) + (meany - j) * (meany - j)) / (2. * sigma * sigma));

			sumR += _originalImage->pixelColor(i, j).red() / 255. * weight;
			sumG += _originalImage->pixelColor(i, j).green() / 255. * weight;
			sumB += _originalImage->pixelColor(i, j).blue() / 255. * weight;

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
	return *_blurredImage;
}

QImage& ImageFilter::getSharpenedImg()
{
	return *_sharpenedImage;
}

ImageFilter::ImageFilter()
{
}

ImageFilter::ImageFilter(QString type, int radius, int amount, QImage* original)
{
	_radius = radius;
	_type = type;
	_amount = amount;
	_originalImage = original;
}


ImageFilter::~ImageFilter()
{
}

QString ImageFilter::getType()
{
	return _type;
}

void ImageFilter::setType(QString type)
{
	_type = type;
}

int ImageFilter::Radius()
{
	return _radius;
}

int ImageFilter::Amount()
{
	return _amount;
}

void ImageFilter::setRadius(int radius)
{
	_radius = radius;
}

void ImageFilter::setAmount(int amount)
{
	_amount = amount;
}

void ImageFilter::applyBlur()
{
	if (_originalImage->isNull()) {
		return;
	}

	int height = _originalImage->height();
	int width = _originalImage->width();
	QImage::Format format = _originalImage->format();

	_blurredImage = new QImage(width, height, format);

	int threadCount = QThreadPool::globalInstance()->maxThreadCount();
	std::cout << "child thread " << std::this_thread::get_id() << ": initiating image processing on " << threadCount << " additional threads..." << std::endl;
	int step = _originalImage->height() / threadCount;

	for (int i = 0; i < threadCount; i++) {
		std::lock_guard<std::mutex> guard(_threadMutex);
		if (i + 1 < threadCount) {
			QtConcurrent::run(this, &ImageFilter::applyBlur, i * step, (i + 1) * step);
			std::cout << "child thread " << std::this_thread::get_id() << ": y from " << i * step << " to " << (i + 1) * step << std::endl;
		} else {
			QtConcurrent::run(this, &ImageFilter::applyBlur, i * step, _originalImage->height());
			std::cout << "child thread " << std::this_thread::get_id() << ": y from " << i * step << " to " << _originalImage->height() << std::endl;
		}
	}
	std::cout << "..." << std::endl;
}



void ImageFilter::applyBlur(int from, int to)
{
	QRgb col;
	for (int y = from; y < to; y++) {
		for (int x = 0; x < _originalImage->width(); x++) {
			std::lock_guard<std::mutex> guard(_kernelMutex);
			col = kernelSum(x, y);
			*((QRgb*)_blurredImage->scanLine(y) + x) = col;
		}		
	}
}

void ImageFilter::applySharpen()
{
	if (_amount > 0) {
		applyBlur();
	
		int height = _blurredImage->height();
		int width = _blurredImage->width();
		QImage::Format format = _blurredImage->format();

		_sharpenedImage = new QImage(width, height, format);

		float redF, greenF, blueF;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				redF = ((float)(_originalImage->pixelColor(x, y).red() + _amount * (_originalImage->pixelColor(x, y).red() - _blurredImage->pixelColor(x, y).red())));
				greenF = ((float)(_originalImage->pixelColor(x, y).green() + _amount * (_originalImage->pixelColor(x, y).green() - _blurredImage->pixelColor(x, y).green())));
				blueF = ((float)(_originalImage->pixelColor(x, y).blue() + _amount * (_originalImage->pixelColor(x, y).blue() - _blurredImage->pixelColor(x, y).blue())));
			
				redF = std::max((float)0., std::min(redF, (float)255.));
				greenF = std::max((float)0., std::min(greenF, (float)255.));
				blueF = std::max((float)0., std::min(blueF, (float)255.));

				QRgb resultColor = QColor(((int)redF + 0.5), ((int)greenF + 0.5), ((int)blueF + 0.5)).rgb();
				*((QRgb*)_sharpenedImage->scanLine(y) + x) = resultColor;
			}
		}
	}
}
