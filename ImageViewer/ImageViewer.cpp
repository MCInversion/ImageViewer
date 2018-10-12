#include "ImageViewer.h"

void ImageViewer::displayImage(QImage *image)
{
	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsView* view = ui.graphicsView;
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
	QPixmap pixmap = QPixmap().fromImage(*image);
	scene->addPixmap(pixmap);
	ui.graphicsView->setScene(scene);
	update();
}

QImage ImageViewer::getResized(QImage *image, const QSize &newSize, bool keepAspectRatio)
{
	QImage resized = image->scaled(newSize, (keepAspectRatio ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio), Qt::FastTransformation);
	return resized;
}

void ImageViewer::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	if (currentImg != NULL) {
		QSize viewerSize = ui.graphicsView->size();
		QImage displayedImg = getResized(currentImg, viewerSize);
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
	currentImg = &getLast();
	QImage displayedImg = getResized(currentImg, viewerSize);
	displayImage(&displayedImg);
	
	return true;
}

bool ImageViewer::saveImage(const QString &fileName)
{
	QImage visibleImage = *currentImg;;

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
	currentImg = &getImage(id);
	QSize viewerSize = ui.graphicsView->size();
	QImage displayedImg = getResized(currentImg, viewerSize);
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