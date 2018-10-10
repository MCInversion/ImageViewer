/********************************************************************************
** Form generated from reading UI file 'ImageViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEWER_H
#define UI_IMAGEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageViewerClass
{
public:
    QAction *actionOpen_Image;
    QAction *actionSave_Image;
    QAction *actionLoadImage;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *FileListWidget;
    QListWidget *listWidget2;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageViewerClass)
    {
        if (ImageViewerClass->objectName().isEmpty())
            ImageViewerClass->setObjectName(QStringLiteral("ImageViewerClass"));
        ImageViewerClass->resize(667, 631);
        actionOpen_Image = new QAction(ImageViewerClass);
        actionOpen_Image->setObjectName(QStringLiteral("actionOpen_Image"));
        actionSave_Image = new QAction(ImageViewerClass);
        actionSave_Image->setObjectName(QStringLiteral("actionSave_Image"));
        actionLoadImage = new QAction(ImageViewerClass);
        actionLoadImage->setObjectName(QStringLiteral("actionLoadImage"));
        centralWidget = new QWidget(ImageViewerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        FileListWidget = new QListWidget(centralWidget);
        FileListWidget->setObjectName(QStringLiteral("FileListWidget"));
        FileListWidget->setMaximumSize(QSize(250, 800));

        verticalLayout->addWidget(FileListWidget);

        listWidget2 = new QListWidget(centralWidget);
        listWidget2->setObjectName(QStringLiteral("listWidget2"));
        listWidget2->setMaximumSize(QSize(250, 500));

        verticalLayout->addWidget(listWidget2);


        horizontalLayout_2->addLayout(verticalLayout);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout_2->addWidget(graphicsView);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        ImageViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageViewerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 667, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        ImageViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageViewerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageViewerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageViewerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen_Image);
        menuFile->addAction(actionSave_Image);

        retranslateUi(ImageViewerClass);
        QObject::connect(actionSave_Image, SIGNAL(triggered()), ImageViewerClass, SLOT(ActionSaveImage()));
        QObject::connect(FileListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), ImageViewerClass, SLOT(ActionLoadImage()));
        QObject::connect(actionOpen_Image, SIGNAL(triggered()), ImageViewerClass, SLOT(ActionOpenImage()));

        QMetaObject::connectSlotsByName(ImageViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageViewerClass)
    {
        ImageViewerClass->setWindowTitle(QApplication::translate("ImageViewerClass", "ImageViewer", Q_NULLPTR));
        actionOpen_Image->setText(QApplication::translate("ImageViewerClass", "Open Image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpen_Image->setToolTip(QApplication::translate("ImageViewerClass", "Open Image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSave_Image->setText(QApplication::translate("ImageViewerClass", "Save Image", Q_NULLPTR));
        actionLoadImage->setText(QApplication::translate("ImageViewerClass", "LoadImage", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("ImageViewerClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageViewerClass: public Ui_ImageViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWER_H
