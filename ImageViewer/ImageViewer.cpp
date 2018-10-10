#include "ImageViewer.h"

void ImageViewer::resizeImage(QImage *image, const QSize &newSize)
{
	if (image->size() == newSize)
		return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}

void ImageViewer::displayImage(QImage *image)
{
	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsView* view = ui.graphicsView;
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(getLast()));
	QPixmap pixmap = QPixmap().fromImage(*image);
	scene -> addPixmap(pixmap);
	ui.graphicsView -> setScene(scene);
	update();
}

void ImageViewer::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
}

bool ImageViewer::openImage(const QString &fileName)
{
	QImage loadedImage;
	if (!loadedImage.load(fileName))
		return false;

	images.push_back(loadedImage);
	displayImage(&getLast());
	
	return true;
}

bool ImageViewer::saveImage(const QString &fileName)
{
	QImage visibleImage = getLast();
	resizeImage(&visibleImage, size());

	if (visibleImage.save(fileName, "png")) {
		return true;
	}
	else {
		return false;
	}
}

QImage ImageViewer::getImage(int i)
{
	return images.at(i);
}

QImage ImageViewer::getLast()
{
	return images.back();
}

ImageViewer::ImageViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
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
	int id = ui.FileListWidget->currentRow();
	displayImage(&getImage(id));
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