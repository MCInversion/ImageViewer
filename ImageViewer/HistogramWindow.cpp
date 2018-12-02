#include "HistogramWindow.h"

HistogramThread::HistogramThread(QObject* parent)
{
	thread = new QThread(parent);
}

HistogramThread::~HistogramThread()
{
	if (thread->isRunning()) {
		thread->terminate();
	}
}

void HistogramWindow::displayImage(QImage * image)
{
	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
	QPixmap pixmap = QPixmap().fromImage(*image);
	scene->addPixmap(pixmap);
	ui.histogramView->setScene(scene);
	update();
}

void HistogramWindow::initThread(QImage targetImage)
{
	_computed_hist_thread = new HistogramThread(this);
	_histogram = new Histogram(&targetImage);
	_histogram->moveToThread(_computed_hist_thread->thread);
	_computed_hist_thread->thread->start();

	connect(this, SIGNAL(histogramLaunched()), _histogram, SLOT(plotHistogram()));
	connect(_histogram, SIGNAL(histogramPlotted()), this, SLOT(actionsAfterCompletion()));

	emit histogramLaunched();
}

void HistogramWindow::initReplotThread()
{
	// do not re-initialize a new thread and move the _histogram object into it when it has already been moved here
	_histogram->moveToThread(_computed_hist_thread->thread);
	_computed_hist_thread->thread->start();

	connect(this, SIGNAL(histogramLaunched()), _histogram, SLOT(plotHistogram()));
	connect(_histogram, SIGNAL(histogramPlotted()), this, SLOT(actionsAfterCompletion()));

	emit histogramLaunched();
}

QImage HistogramWindow::getResized(QImage * image, const QSize & newSize, bool keepAspectRatio)
{
	return image->scaled(newSize, (keepAspectRatio ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio), Qt::FastTransformation);
}

HistogramWindow::HistogramWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

HistogramWindow::~HistogramWindow()
{
	if (_histogram != NULL) {
		delete _histogram;
	}
}

void HistogramWindow::actionsAfterCompletion()
{
	QSize viewerSize = ui.histogramView->size();
	QImage viewed = getResized(&_histogram->getHistogramPlot(), viewerSize, true);
	displayImage(&viewed);

	if (_computed_hist_thread != NULL) {
		_computed_hist_thread->thread->exit(1);
	}
	if (_progressBar != NULL) {
		delete _progressBar;
		_progressBar = NULL;
	}
}

void HistogramWindow::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	if (_histogram != NULL && _histogram->isPlotted()) {
		QSize viewerSize = ui.histogramView->size();
		QImage displayedImg(_histogram->getHistogramPlot());
		displayedImg = getResized(&displayedImg, viewerSize, true);
		displayImage(&displayedImg);
	}	
}

void HistogramWindow::closeEvent(QCloseEvent *event)
{
	QWidget::closeEvent(event);

	if (_computed_hist_thread != NULL && _computed_hist_thread->thread->isRunning()) {
		_computed_hist_thread->thread->terminate();
	}
}

void HistogramWindow::ActionReplot()
{
	if (_histogram != NULL) {
		_histogram->RED_setEnabled(ui.redCheckBox->isChecked());
		_histogram->GREEN_setEnabled(ui.greenCheckBox->isChecked());
		_histogram->BLUE_setEnabled(ui.blueCheckBox->isChecked());

		if (_histogram->isPlotted()) {
			initReplotThread();
		}	
	}
}

void Histogram::drawLine(const QPoint & startPt, const QPoint & endPt, QColor color, int width)
{
	QPainter painter(_histogramPlot);
	painter.setPen(QPen(color, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawLine(startPt, endPt);
}

Histogram::Histogram()
{
}

Histogram::Histogram(QImage *targetImage)
{
	_targetImage = new QImage(*targetImage);
}

Histogram::~Histogram()
{
}

void Histogram::computeHistogram()
{
	int height = _targetImage->height();
	int width = _targetImage->width();
	_max_value = 0;
	int red_id, green_id, blue_id;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			red_id = _targetImage->pixelColor(x, y).red();
			green_id = _targetImage->pixelColor(x, y).green();
			blue_id = _targetImage->pixelColor(x, y).blue();
			_count_RED[red_id]++;
			_count_GREEN[green_id]++;
			_count_BLUE[blue_id]++;
			if (_count_RED[red_id] > _max_value) _max_value = _count_RED[red_id];
			if (_count_GREEN[green_id] > _max_value) _max_value = _count_GREEN[green_id];
			if (_count_BLUE[blue_id] > _max_value) _max_value = _count_BLUE[blue_id];
		}
	}

	_computed = true;
}

void Histogram::plotHistogram()
{
	if (!_computed) {
		computeHistogram();
	}

	int width = 400;
	int height = 300;
	int y_offset = 0.1 * height;
	_histogramPlot = new QImage(width, height, QImage::Format_RGB32);
	_histogramPlot->fill(qRgb(255, 255, 255));
	int width_step = ((int)(width / 256. + 0.5));
	float normalization_value = ((float)(1.1 * _max_value));
	float normalizedValue0, normalizedValue1;
	int x0, x1, y0, y1;
	drawLine(QPoint(0, height - y_offset), QPoint(width, height - y_offset), QColor(0, 0, 0), 2); // x-axis
	drawLine(QPoint(0, height - y_offset), QPoint(0, y_offset), QColor(0, 0, 0), 2); // y-axis

	for (int i = 0; i < 255; i++) {
		if (_show_RED) {
			normalizedValue0 = (float)_count_RED[i] / normalization_value;
			normalizedValue1 = (float)_count_RED[i + 1] / normalization_value;
			x0 = i * width_step, x1 = (i + 1) * width_step;
			y0 = ((int)(normalizedValue0 * height + 0.5)) + y_offset;
			y1 = ((int)(normalizedValue1 * height + 0.5)) + y_offset;
			drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(255, 0, 0), 3);
		}

		if (_show_GREEN) {
			normalizedValue0 = (float)_count_GREEN[i] / normalization_value;
			normalizedValue1 = (float)_count_GREEN[i + 1] / normalization_value;
			x0 = i * width_step, x1 = (i + 1) * width_step;
			y0 = ((int)(normalizedValue0 * height + 0.5)) + y_offset;
			y1 = ((int)(normalizedValue1 * height + 0.5)) + y_offset;
			drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(0, 255, 0), 3);
		}

		if (_show_BLUE) {
			normalizedValue0 = (float)_count_BLUE[i] / normalization_value;
			normalizedValue1 = (float)_count_BLUE[i + 1] / normalization_value;
			x0 = i * width_step, x1 = (i + 1) * width_step;
			y0 = ((int)(normalizedValue0 * height + 0.5)) + y_offset;
			y1 = ((int)(normalizedValue1 * height + 0.5)) + y_offset;
			drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(0, 0, 255), 3);
		}
	}

	emit histogramPlotted();
}

QImage Histogram::getHistogramPlot()
{
	if (_histogramPlot != NULL) {
		return *_histogramPlot;
	}
	else {
		return QImage();
	}	
}

bool Histogram::isPlotted()
{
	return _histogramPlot != NULL;
}

void Histogram::RED_setEnabled(bool value)
{
	_show_RED = value;
}

void Histogram::GREEN_setEnabled(bool value)
{
	_show_GREEN = value;
}

void Histogram::BLUE_setEnabled(bool value)
{
	_show_BLUE = value;
}
