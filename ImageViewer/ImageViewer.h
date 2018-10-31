#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "qlayoutitem.h"
#include "ui_ImageViewer.h"
#include "ImageFilter.h"
#include <vector>
#include <thread>
#include <QDebug>
#include <QtGui>

class ImageViewer : public QMainWindow
{
	Q_OBJECT

public:
	ImageViewer(QWidget *parent = Q_NULLPTR);
public slots:
	void ActionOpenImage();
	void ActionLoadImage();
	void ActionSaveImage();

	void ActionChangeRadius();
	void ActionChangeAmount();

	void ActionBlur();
	void ActionSharpen();
	QImage getImage(int i);
	QImage getLast();
protected:
	void resizeEvent(QResizeEvent *event);
	//void keyPressEvent(QKeyEvent *event);
private:
	Ui::ImageViewerClass ui;
	QList<QImage> images;
	int currentImgId = -1;

	QImage getResized(QImage *image, const QSize &newSize, bool keepAspectRatio = true);
	void replaceImageAt(QImage *replacement, int i);
	bool openImage(const QString &fileName);
	bool saveImage(const QString &fileName);
	void displayImage(QImage *image);
	void removeSelected();
	bool eventFilter(QObject* object, QEvent* event);
	void clearViewer();
};
