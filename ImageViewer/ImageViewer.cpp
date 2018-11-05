#include "ImageViewer.h"

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

void ImageViewer::replaceImageAt(std::future<QImage>& futureReplacement, int i)
{
	QImage replacement = futureReplacement.get();
	images.replace(i, FilteredImage(&replacement));
	QSize viewerSize = ui.graphicsView->size();
	bool keepAspectRatio = ui.checkBox->isChecked();
	QImage viewed = getResized(&getImage(i), viewerSize, keepAspectRatio);
	displayImage(&viewed);
}

void ImageViewer::replaceImageAt(QImage *replacement, int i)
{
	images.replace(i, FilteredImage(replacement));
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
		QImage displayedImg(*images.at(currentImgId).originalImage);
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

	images.push_back(FilteredImage(&loadedImage));
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

QImage ImageViewer::getImage(int i)
{
	return *images.at(i).originalImage;
}

QImage ImageViewer::getLast()
{
	return *images.back().originalImage;
}

ImageViewer::ImageViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	installEventFilter(this);
	QTimer timer = QTimer(this);
	connect(&timer, SIGNAL(timeout()), this, SLOT(checkIfDone()));
	timer.start(1000);
}

void ImageViewer::ActionOpenImage()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "image files (*.png *.jpg *.bmp)");
	if (!fileName.isEmpty()) {
		openImage(fileName);
		int lastrow = ui.FileListWidget -> count();
		QString name = fileName.split("/").last();
		ui.FileListWidget -> insertItem(lastrow, name);
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

void ImageViewer::ActionBlur()
{
	if (currentImgId != -1) {
		int radius = ui.radiusSlider->value();
		int amount = ui.amountSlider->value();
		FilteredImage target = images.at(currentImgId);
		ImageFilter blur("blur", radius, amount, &target);

		std::cout << "main thread " << std::this_thread::get_id() << ": init " << std::endl;
		// QtConcurrent::run(&blur, &ImageFilter::applyBlur);
		startBlurComputationThread(&blur);

		/*QThreadPool::globalInstance()->waitForDone(); // waiting freezes the GUI
		std::cout << "main thread " << std::this_thread::get_id() << ": finished " << std::endl;
		QImage result = blur.getBlurredImg();
		replaceImageAt(&result, currentImgId); */
	}	
}

void ImageViewer::ActionSharpen()
{
	if (currentImgId != -1) {
		int radius = ui.radiusSlider->value();
		int amount = ui.amountSlider->value();
		FilteredImage target = images.at(currentImgId);
		ImageFilter sharpen("sharpen", radius, amount, &target);

		std::cout << "main thread " << std::this_thread::get_id() << ": init " << std::endl;
		QtConcurrent::run(&sharpen, &ImageFilter::applySharpen);

		QThreadPool::globalInstance()->waitForDone(); // waiting freezes the GUI
		std::cout << "main thread " << std::this_thread::get_id() << ": finished " << std::endl;
		QImage result = sharpen.getSharpenedImg();
		replaceImageAt(&result, currentImgId);
	}
}

/*
void ImageViewer::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Return:
	case Qt::Key_Enter:
		qDebug() << "Enter";
		break;
	case Qt::Key_Escape:
		qDebug() << "Escape";
		break;
	case Qt::Key_Insert:
		qDebug() << "Insert";
		break;
	case Qt::Key_Delete:
		qDebug() << "Delete";
		break;
	default:
		qDebug() << "other" << event->key();
		break;
	}
}*/

void ImageViewer::clearViewer()
{
	ui.graphicsView-> setScene(new QGraphicsScene());
}

void ImageViewer::checkIfDone()
{
	if (_running_process_th.joinable() && _filter_computation_started) {
		replaceImageAt(images.at(currentImgId).processedImage, currentImgId);
	}
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

std::thread& ImageViewer::getRunningThread()
{
	return _running_process_th;
}

void ImageViewer::startBlurComputationThread(ImageFilter *filter)
{
	_filter_computation_started = true;
	_running_process_th = std::thread([&]() {
		filter->applyBlur();
	});
}
