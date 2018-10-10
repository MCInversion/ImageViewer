#include "ImageViewer.h"

void ImageViewer::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
}

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

bool ImageViewer::openImage(const QString &fileName)
{
	QImage loadedImage;
	if (!loadedImage.load(fileName))
		return false;

	QSize newSize = loadedImage.size();
	resizeImage(&loadedImage, newSize);
	images.push_back(loadedImage);
	//ui.graphicsView->resize(newSize);

	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsView* view = ui.graphicsView;
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(getLast()));
	QPixmap pixmap(fileName);
	scene -> addPixmap(pixmap);
	ui.graphicsView -> setScene(scene);
	update();
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

void ImageViewer::ActionLoadImage()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "image files (*.png *.jpg *.bmp)");
	if (!fileName.isEmpty()) {
		openImage(fileName);
		int lastrow = ui.FileListWidget -> count();
		QString name = fileName.split("/").last();
		ui.FileListWidget -> insertItem(lastrow, name);
	}		
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