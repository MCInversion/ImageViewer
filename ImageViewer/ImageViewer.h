#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include "qlayoutitem.h"
#include "ui_ImageViewer.h"

class ImageViewer : public QMainWindow
{
	Q_OBJECT

public:
	ImageViewer(QWidget *parent = Q_NULLPTR);
public slots:
	void ActionLoadImage();
	void ActionSaveImage();
private:
	Ui::ImageViewerClass ui;
};
