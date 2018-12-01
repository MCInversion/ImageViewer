#include "HistogramWindow.h"

void HistogramWindow::displayImage(QImage * image)
{
	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
	QPixmap pixmap = QPixmap().fromImage(*image);
	scene->addPixmap(pixmap);
	ui.histogramView->setScene(scene);
	update();
}

void HistogramWindow::drawLine(const QPoint &startPt, const QPoint &endPt, QColor color, int width)
{
	QPainter painter(_histogramPlot);
	painter.setPen(QPen(color, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawLine(startPt, endPt);
	update();
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
	if (_histogramPlot != NULL || _targetImage != NULL) {
		delete _histogramPlot;
		delete _targetImage;
	}
}

void HistogramWindow::ShowHistogram(QImage targetImage)
{
	if (!_computed && _targetImage == NULL) {
		_targetImage = new QImage(targetImage);
		computeHistogram(&targetImage);
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

	for (int i = 0; i < 255; i++) {
		if (ui.redCheckBox->isChecked()) {
			normalizedValue0 = (float)_count_RED[i] / normalization_value;
			normalizedValue1 = (float)_count_RED[i + 1] / normalization_value;
			x0 = i * width_step, x1 = (i + 1) * width_step;
			y0 = ((int)(normalizedValue0 * height + 0.5)) + y_offset;
			y1 = ((int)(normalizedValue1 * height + 0.5)) + y_offset;
			drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(255, 0, 0), 3);
		}		

		if (ui.greenCheckBox->isChecked()) {
			normalizedValue0 = (float)_count_GREEN[i] / normalization_value;
			normalizedValue1 = (float)_count_GREEN[i + 1] / normalization_value;
			x0 = i * width_step, x1 = (i + 1) * width_step;
			y0 = ((int)(normalizedValue0 * height + 0.5)) + y_offset;
			y1 = ((int)(normalizedValue1 * height + 0.5)) + y_offset;
			drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(0, 255, 0), 3);
		}
		
		if (ui.blueCheckBox->isChecked()) {
			normalizedValue0 = (float)_count_BLUE[i] / normalization_value;
			normalizedValue1 = (float)_count_BLUE[i + 1] / normalization_value;
			x0 = i * width_step, x1 = (i + 1) * width_step;
			y0 = ((int)(normalizedValue0 * height + 0.5)) + y_offset;
			y1 = ((int)(normalizedValue1 * height + 0.5)) + y_offset;
			drawLine(QPoint(x0, height - y0), QPoint(x1, height - y1), QColor(0, 0, 255), 3);
		}
	}

	QSize viewerSize = ui.histogramView->size();
	QImage viewed = getResized(_histogramPlot, viewerSize, true);
	displayImage(&viewed);
}

void HistogramWindow::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	if (_histogramPlot != NULL) {
		QSize viewerSize = ui.histogramView->size();
		QImage displayedImg(*_histogramPlot);
		displayedImg = getResized(&displayedImg, viewerSize, true);
		displayImage(&displayedImg);
	}	
}

void HistogramWindow::closeEvent(QCloseEvent *event)
{
	QWidget::closeEvent(event);
}

void HistogramWindow::computeHistogram(QImage *targetImage)
{
	int height = targetImage->height();
	int width = targetImage->width();
	_max_value = 0;
	int red_id, green_id, blue_id;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			red_id = targetImage->pixelColor(x, y).red();
			green_id = targetImage->pixelColor(x, y).green();
			blue_id = targetImage->pixelColor(x, y).blue();
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

void HistogramWindow::ActionReplot()
{
	if (_targetImage != NULL) {
		ShowHistogram(*_targetImage);
	}	
}
