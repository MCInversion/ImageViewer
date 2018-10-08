#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void ImageViewer::ActionLoadImage()
{




	printf("loading image\n");
}

void ImageViewer::ActionSaveImage()
{
	printf("saving image\n");
}
