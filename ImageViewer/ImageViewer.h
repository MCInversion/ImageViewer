#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "qlayoutitem.h"
#include "ui_ImageViewer.h"
#include <vector>

class ImageViewer : public QMainWindow
{
	Q_OBJECT

public:
	ImageViewer(QWidget *parent = Q_NULLPTR);
public slots:
	void ActionLoadImage();
	void ActionSaveImage();
	void resizeImage(QImage *image, const QSize &newSize);
	bool openImage(const QString &fileName);
	bool saveImage(const QString &fileName);
	QImage getImage(int i);
	QImage getLast();
protected:
	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
private:
	Ui::ImageViewerClass ui;
	std::vector<QImage> images;
};
