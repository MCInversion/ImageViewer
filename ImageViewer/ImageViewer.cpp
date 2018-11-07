#include "ImageViewer.h"


QRgb ImageFilter::kernelSum(int x, int y)
{
	int meanx = x;
	int meany = y;
	int ix, iy, jx, jy;

	int height = _originalImage.height();
	int width = _originalImage.width();

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

			sumR += _originalImage.pixelColor(i, j).red() / 255. * weight;
			sumG += _originalImage.pixelColor(i, j).green() / 255. * weight;
			sumB += _originalImage.pixelColor(i, j).blue() / 255. * weight;

			wsum += weight;
		}
	}

	int red = std::min(((int)((sumR / wsum) * 255 + 0.5)), 255);
	int green = std::min(((int)((sumG / wsum) * 255 + 0.5)), 255);
	int blue = std::min(((int)((sumB / wsum) * 255 + 0.5)), 255);

	return QColor(red, green, blue).rgb();
}

QImage ImageFilter::getOriginalImg()
{
	return _originalImage;
}

QImage ImageFilter::getBlurredImg()
{
	return _blurredImage;
}

QImage ImageFilter::getSharpenedImg()
{
	return _sharpenedImage;
}

ImageFilter::ImageFilter(QObject* parent): QObject(parent)
{
}

ImageFilter::ImageFilter(QString type, int radius, int amount, QImage original, QObject* parent)
	: QObject(parent)
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
	if (_originalImage.isNull()) {
		return;
	}

	int height = _originalImage.height();
	int width = _originalImage.width();
	QImage::Format format = _originalImage.format();

	_blurredImage = QImage(width, height, format);
	QRgb resultColor;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			resultColor = kernelSum(x, y);
			*((QRgb*)_blurredImage.scanLine(y) + x) = resultColor;			
		}
	}

	emit filterComputationComplete();
}

void ImageFilter::applySharpen()
{
	if (_originalImage.isNull() || _amount == 0) {
		return;
	}

	int height = _originalImage.height();
	int width = _originalImage.width();
	QImage::Format format = _originalImage.format();

	_blurredImage = QImage(width, height, format);
	_sharpenedImage = QImage(width, height, format);

	QRgb resultColor;
	float redF, greenF, blueF;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			resultColor = kernelSum(x, y);
			*((QRgb*)_blurredImage.scanLine(y) + x) = resultColor;

			redF = ((float)(_originalImage.pixelColor(x, y).red() + _amount * (_originalImage.pixelColor(x, y).red() - _blurredImage.pixelColor(x, y).red())));
			greenF = ((float)(_originalImage.pixelColor(x, y).green() + _amount * (_originalImage.pixelColor(x, y).green() - _blurredImage.pixelColor(x, y).green())));
			blueF = ((float)(_originalImage.pixelColor(x, y).blue() + _amount * (_originalImage.pixelColor(x, y).blue() - _blurredImage.pixelColor(x, y).blue())));

			redF = std::max((float)0., std::min(redF, (float)255.));
			greenF = std::max((float)0., std::min(greenF, (float)255.));
			blueF = std::max((float)0., std::min(blueF, (float)255.));

			QRgb resultColor = QColor(((int)redF + 0.5), ((int)greenF + 0.5), ((int)blueF + 0.5)).rgb();
			*((QRgb*)_sharpenedImage.scanLine(y) + x) = resultColor;
		}
	}

	emit filterComputationComplete();
}


void ImageViewer::displayImage(QImage *image)
{
	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
	QPixmap pixmap = QPixmap().fromImage(*image);
	scene->addPixmap(pixmap);
	ui.graphicsView->setScene(scene);
	update();
}

QImage ImageViewer::getResized(QImage *image, const QSize &newSize, bool keepAspectRatio)
{
	return image->scaled(newSize, (keepAspectRatio ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio), Qt::FastTransformation);
}

void ImageViewer::replaceImageAt(QImage replacement, int i)
{
	images.replace(i, replacement);
	QSize viewerSize = ui.graphicsView->size();
	bool keepAspectRatio = ui.checkBox->isChecked();
	QImage viewed = getResized(&getImage(i), viewerSize, keepAspectRatio);
	displayImage(&viewed);
}

void ImageViewer::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	if (currentImgId > -1) {
		QSize viewerSize = ui.graphicsView->size();
		QImage displayedImg(images.at(currentImgId));
		bool keepAspectRatio = ui.checkBox->isChecked();
		displayedImg = getResized(&displayedImg, viewerSize, keepAspectRatio);
		displayImage(&displayedImg);
	}
}

bool ImageViewer::openImage(const QString &fileName)
{
	QImage loadedImage;
	if (!loadedImage.load(fileName))
		return false;

	images.push_back(loadedImage);
	QSize viewerSize = ui.graphicsView->size();
	currentImgId = images.size() - 1;
	bool keepAspectRatio = ui.checkBox->isChecked();
	QImage displayedImg = getResized(&getLast(), viewerSize, keepAspectRatio);
	displayImage(&displayedImg);

	return true;
}

bool ImageViewer::saveImage(const QString &fileName)
{
	QImage visibleImage = getImage(currentImgId);

	if (visibleImage.save(fileName, "png")) {
		return true;
	}
	else {
		return false;
	}
}

ImageViewer::~ImageViewer()
{
	_process_thread->exit();
}

QImage ImageViewer::getImage(int i)
{
	return images.at(i);
}

QImage& ImageViewer::getLast()
{
	return images.back();
}

ImageViewer::ImageViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	installEventFilter(this);
}

void ImageViewer::ActionOpenImage()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "image files (*.png *.jpg *.bmp)");
	if (!fileName.isEmpty()) {
		openImage(fileName);
		int lastrow = ui.FileListWidget->count();
		QString name = fileName.split("/").last();
		ui.FileListWidget->insertItem(lastrow, name);
	}
}

void ImageViewer::ActionLoadImage()
{
	currentImgId = ui.FileListWidget->currentRow();
	QSize viewerSize = ui.graphicsView->size();
	bool keepAspectRatio = ui.checkBox->isChecked();
	QImage displayedImg = getResized(&getImage(currentImgId), viewerSize, keepAspectRatio);
	displayImage(&displayedImg);
}

void ImageViewer::ActionSaveImage()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), "untitled.png", tr("png Files (*.png)"));
	if (fileName.isEmpty()) {
		return;
	}
	else {
		saveImage(fileName);
	}
}

void ImageViewer::ActionChangeRadius()
{
	int value = ui.radiusSlider->value();
	QString display = QString::number(value) + QString(" px");
	ui.radiusLabel->setText(display);
}

void ImageViewer::ActionChangeAmount()
{
	int value = ui.amountSlider->value();
	QString display = QString::number(value) + QString(" %");
	ui.amountLabel->setText(display);
}

void ImageViewer::startBlurComputationThread(int radius, int amount, QImage original)
{
	_process_thread = new QThread(this);	
	_activeFilter = new ImageFilter("blur", radius, amount, original);

	_activeFilter->moveToThread(_process_thread);
	_process_thread->start();
	connect(this, &ImageViewer::launchComputation, _activeFilter, &ImageFilter::applyBlur);
	connect(_activeFilter, &ImageFilter::filterComputationComplete, this, &ImageViewer::actionsAfterCompletion);

	emit launchComputation();
}

void ImageViewer::startSharpenComputationThread(int radius, int amount, QImage original)
{
	_process_thread = new QThread(this);	
	_activeFilter = new ImageFilter("sharpen", radius, amount, original);

	_activeFilter->moveToThread(_process_thread);
	_process_thread->start();

	connect(this, &ImageViewer::launchComputation, _activeFilter, &ImageFilter::applySharpen);
	connect(_activeFilter, &ImageFilter::filterComputationComplete, this, &ImageViewer::actionsAfterCompletion);

	emit launchComputation();
}

void ImageViewer::ActionBlur()
{
	if (currentImgId != -1 && !_filter_computation_started) {
		int radius = ui.radiusSlider->value();
		int amount = ui.amountSlider->value();
		processedImgId = currentImgId;
		_processedImage = images.at(processedImgId);

		startBlurComputationThread(radius, amount, _processedImage);
	}
}

void ImageViewer::ActionSharpen()
{
	if (currentImgId != -1 && !_filter_computation_started) {
		int radius = ui.radiusSlider->value();
		int amount = ui.amountSlider->value();
		processedImgId = currentImgId;
		_processedImage = images.at(processedImgId);

		startSharpenComputationThread(radius, amount, _processedImage);
	}
}

void ImageViewer::actionsAfterCompletion()
{
	if (_activeFilter->getType() == "blur") {
		replaceImageAt(_activeFilter->getBlurredImg(), processedImgId);
	}
	else if (_activeFilter->getType() == "sharpen") {
		replaceImageAt(_activeFilter->getSharpenedImg(), processedImgId);
	}
	_process_thread->exit(1);
}

void ImageViewer::clearViewer()
{
	ui.graphicsView->setScene(new QGraphicsScene());
}

void ImageViewer::removeSelected()
{
	QList<QListWidgetItem*> selection = ui.FileListWidget->selectedItems();
	if (!selection.isEmpty()) {
		qDeleteAll(ui.FileListWidget->selectedItems());

		if (images.size() > 1) {
			QSize viewerSize = ui.graphicsView->size();
			bool keepAspectRatio = ui.checkBox->isChecked();
			QImage displayedImg = getResized(&getImage(0), viewerSize, keepAspectRatio);
			displayImage(&displayedImg);

			currentImgId = 0;
		}
		else {
			clearViewer();
			images.removeAt(currentImgId);
			currentImgId = -1;
		}
	}
}

bool ImageViewer::eventFilter(QObject *object, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* pKeyEvent = static_cast<QKeyEvent*>(event);
		if (pKeyEvent->key() == Qt::Key_Delete)
		{
			if (ui.FileListWidget->hasFocus())
			{
				removeSelected();
			}
			return true;
		}
	}
	return QWidget::eventFilter(object, event);
}
