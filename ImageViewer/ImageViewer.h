#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "qlayoutitem.h"
#include "ui_ImageViewer.h"
#include <vector>
#include <QDebug>

class ImageViewer : public QMainWindow
{
	Q_OBJECT

public:
	ImageViewer(QWidget *parent = Q_NULLPTR);
public slots:
	void ActionOpenImage();
	void ActionLoadImage();
	void ActionSaveImage();
	QImage getResized(QImage *image, const QSize &newSize, bool keepAspectRatio = true);
	bool openImage(const QString &fileName);
	bool saveImage(const QString &fileName);
	void displayImage(QImage *image);
	QImage getImage(int i);
	QImage getLast();
protected:
	void resizeEvent(QResizeEvent *event);
private:
	Ui::ImageViewerClass ui;
	std::vector<QImage> images;
	QImage *currentImg = NULL;
};
