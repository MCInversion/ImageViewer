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

void HistogramWindow::initProgress()
{
	_computation_progress = 0;
	_status_bar = new QStatusBar(this);
	_bar = new QProgressBar();

	_bar->setRange(0, 100);
	_bar->setValue(0);
	_bar->setTextVisible(true);

	ui.progressBarLayout->addWidget(_status_bar);
	_status_bar->addPermanentWidget(_bar, 2);
}

void HistogramWindow::showProgress()
{
	if (_bar != NULL && _computation_progress <= 100 && _computation_progress >= 0) {
		QString progressMessage = " histogram: " + QString::number(_computation_progress) + "%";
		_bar->setFormat(progressMessage);
		_bar->setValue(_computation_progress);
	}
}

void HistogramWindow::initThread(QImage targetImage)
{
	_computed_hist_thread = new HistogramThread(this);
	_histogram = new Histogram(&targetImage);
	_histogram->moveToThread(_computed_hist_thread->thread);
	_computed_hist_thread->thread->start();

	connect(this, SIGNAL(histogramLaunched()), _histogram, SLOT(plotHistogram()));
	connect(_histogram, SIGNAL(histogramPlotted()), this, SLOT(actionsAfterCompletion()));

	connect(_histogram, SIGNAL(progressIncremented()), this, SLOT(incrementProgress()));
	initProgress();
	showProgress();

	emit histogramLaunched();
}

void HistogramWindow::initReplotThread()
{
	// do not re-initialize a new thread and move the _histogram object into it when it has already been moved here
	_histogram->moveToThread(_computed_hist_thread->thread);
	_computed_hist_thread->thread->start();

	connect(this, SIGNAL(histogramLaunched()), _histogram, SLOT(plotHistogram()));
	connect(_histogram, SIGNAL(histogramPlotted()), this, SLOT(actionsAfterCompletion()));

	connect(_histogram, SIGNAL(progressIncremented()), this, SLOT(incrementProgress()));
	initProgress();
	showProgress();

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
	if (_status_bar != NULL && _bar != NULL) {
		ui.progressBarLayout->removeWidget(_status_bar);
		delete _bar;
		delete _status_bar;
		_bar = NULL;
		_status_bar = NULL;
	}
}

void HistogramWindow::incrementProgress()
{
	_computation_progress++;
	showProgress();
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

void Histogram::drawText(QString text, const QPoint & position, QColor color, int width)
{
	QPainter painter(_histogramPlot);
	painter.setPen(QPen(color, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawText(position.x(), position.y(), 15 * width, 20 * width, Qt::AlignLeft, text);
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

	_progress_percent = ((int)((width * height + 256) / 100. + 0.5));

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

			_progress++;

			if (_progress % _progress_percent == 0) {
				emit progressIncremented();
			}
		}
	}

	_computed = true;
}

void Histogram::plotHistogram()
{
	_progress = 0;
	int pen_width = 5;

	if (!_computed) {
		computeHistogram();
	}
	else {
		_progress_percent = ((int)(256 / 100. + 0.5));
	}

	int width = 800;
	int height = 600;
	int y_offset = 0.1 * height;
	_histogramPlot = new QImage(width, height, QImage::Format_RGB32);
	_histogramPlot->fill(qRgb(255, 255, 255));
	int width_step = ((int)(width / 256. + 0.5));
	float normalization_value = ((float)(_max_value));
	float normalizedValue0, normalizedValue1;
	int x0, x1, y0, y1;
	drawLine(QPoint(0, height - y_offset), QPoint(width - 10 * width_step, height - y_offset), QColor(0, 0, 0), pen_width); // x-axis
	// ticks
	drawText(
		QString::number(0),
		QPoint(0, (int)(height - (1 - 0.2) * y_offset)),
		QColor(0, 0, 0), pen_width
	);
	for (int i = 1; i < 51; i++) {
		float tick_size = i % 2 == 0 ? 0.4 : 0.2;
		drawLine(
			QPoint(5 * i * width_step, (int)(height - (1 + 0.5 * tick_size) * y_offset)),
			QPoint(5 * i * width_step, (int)(height - (1 - 0.5 * tick_size) * y_offset)),
			QColor(0, 0, 0), pen_width);
		if (i % 10 == 0) {
			drawText(
				QString::number(5 * i),
				QPoint(5 * i * width_step, (int)(height - (1 - 0.2) * y_offset)),
				QColor(0, 0, 0), pen_width
			);
		}
	}
	drawText(
		QString::number(255),
		QPoint(width - 8 * width_step, (int)(height - y_offset)),
		QColor(0, 0, 0), pen_width
	);
	drawText(
		QString::number(_max_value),
		QPoint(width - 9 * width_step, y_offset),
		QColor(0, 0, 0), (int)(0.3 * pen_width)
	);
	drawText(
		QString::number((int)(0.5 * _max_value + 0.5)),
		QPoint(width - 9 * width_step, (int)(0.5 * height + 0.5)),
		QColor(0, 0, 0), (int)(0.3 * pen_width)
	);

	drawLine(QPoint(0, height - y_offset), QPoint(0, y_offset), QColor(0, 0, 0), pen_width); // y-axis
	drawLine(QPoint(width - 10 * width_step, height - y_offset), QPoint(width - 10 * width_step, y_offset), QColor(0, 0, 0), (int)(0.5 * pen_width + 0.5));
	drawLine(QPoint(0, y_offset), QPoint(width - 10 * width_step, y_offset), QColor(0, 0, 0), (int)(0.5 * pen_width + 0.5));

	for (int i = 0; i < 255; i++) {
		if (_show_RED) {
			normalizedValue0 = (float)_count_RED[i] / normalization_value;
			normalizedValue1 = (float)_count_RED[i + 1] / normalization_value;
			x0 = i * width_step, x1 = (i + 1) * width_step;
			y0 = ((int)(normalizedValue0 * (height - 2 * y_offset) + 0.5)) + y_offset;
			y1 = ((int)(normalizedValue1 * (height - 2 * y_offset) + 0.5)) + y_offset;
			drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(255, 0, 0), pen_width);
		}

		if (_show_GREEN) {
			normalizedValue0 = (float)_count_GREEN[i] / normalization_value;
			normalizedValue1 = (float)_count_GREEN[i + 1] / normalization_value;
			x0 = i * width_step, x1 = (i + 1) * width_step;
			y0 = ((int)(normalizedValue0 * (height - 2 * y_offset) + 0.5)) + y_offset;
			y1 = ((int)(normalizedValue1 * (height - 2 * y_offset) + 0.5)) + y_offset;
			drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(0, 255, 0), pen_width);
		}

		if (_show_BLUE) {
			normalizedValue0 = (float)_count_BLUE[i] / normalization_value;
			normalizedValue1 = (float)_count_BLUE[i + 1] / normalization_value;
			x0 = i * width_step, x1 = (i + 1) * width_step;
			y0 = ((int)(normalizedValue0 * (height - 2 * y_offset) + 0.5)) + y_offset;
			y1 = ((int)(normalizedValue1 * (height - 2 * y_offset) + 0.5)) + y_offset;
			drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(0, 0, 255), pen_width);
		}

		_progress++;

		if (_progress % _progress_percent == 0) {
			emit progressIncremented();
		}
	}

	if (_show_RED) {
		normalizedValue0 = (float)_count_RED[255] / normalization_value;
		normalizedValue1 = 0.;
		x0 = 255 * width_step, x1 = 256 * width_step;
		y0 = ((int)(normalizedValue0 * (height - 2 * y_offset) + 0.5)) + y_offset;
		y1 = ((int)(normalizedValue1 * (height - 2 * y_offset) + 0.5)) + y_offset;
		drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(255, 0, 0), pen_width);
	}

	if (_show_GREEN) {
		normalizedValue0 = (float)_count_GREEN[255] / normalization_value;
		normalizedValue1 = 0.;
		x0 = 255 * width_step, x1 = 256 * width_step;
		y0 = ((int)(normalizedValue0 * (height - 2 * y_offset) + 0.5)) + y_offset;
		y1 = ((int)(normalizedValue1 * (height - 2 * y_offset) + 0.5)) + y_offset;
		drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(0, 255, 0), pen_width);
	}

	if (_show_BLUE) {
		normalizedValue0 = (float)_count_BLUE[255] / normalization_value;
		normalizedValue1 = 0.;
		x0 = 255 * width_step, x1 = 256 * width_step;
		y0 = ((int)(normalizedValue0 * (height - 2 * y_offset) + 0.5)) + y_offset;
		y1 = ((int)(normalizedValue1 * (height - 2 * y_offset) + 0.5)) + y_offset;
		drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(0, 0, 255), pen_width);
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
