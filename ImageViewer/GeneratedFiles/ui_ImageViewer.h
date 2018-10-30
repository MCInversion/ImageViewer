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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
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
    QAction *actionBlur;
    QAction *actionSharpen;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *FileListWidget;
    QCheckBox *checkBox;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QFrame *line;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuFilter;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageViewerClass)
    {
        if (ImageViewerClass->objectName().isEmpty())
            ImageViewerClass->setObjectName(QStringLiteral("ImageViewerClass"));
        ImageViewerClass->resize(681, 787);
        actionOpen_Image = new QAction(ImageViewerClass);
        actionOpen_Image->setObjectName(QStringLiteral("actionOpen_Image"));
        actionSave_Image = new QAction(ImageViewerClass);
        actionSave_Image->setObjectName(QStringLiteral("actionSave_Image"));
        actionLoadImage = new QAction(ImageViewerClass);
        actionLoadImage->setObjectName(QStringLiteral("actionLoadImage"));
        actionBlur = new QAction(ImageViewerClass);
        actionBlur->setObjectName(QStringLiteral("actionBlur"));
        actionSharpen = new QAction(ImageViewerClass);
        actionSharpen->setObjectName(QStringLiteral("actionSharpen"));
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
        FileListWidget->setMaximumSize(QSize(320, 800));

        verticalLayout->addWidget(FileListWidget);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        verticalLayout->addWidget(checkBox);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(315, 150));
        groupBox->setMaximumSize(QSize(315, 150));
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 20, 311, 121));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkBox_2 = new QCheckBox(verticalLayoutWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout_2->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(verticalLayoutWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        verticalLayout_2->addWidget(checkBox_3);


        verticalLayout->addWidget(groupBox);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        horizontalLayout_2->addLayout(verticalLayout);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout_2->addWidget(graphicsView);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        ImageViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageViewerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 681, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFilter = new QMenu(menuBar);
        menuFilter->setObjectName(QStringLiteral("menuFilter"));
        ImageViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageViewerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageViewerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageViewerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuFilter->menuAction());
        menuFile->addAction(actionOpen_Image);
        menuFile->addAction(actionSave_Image);
        menuFilter->addAction(actionBlur);
        menuFilter->addAction(actionSharpen);

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
        actionBlur->setText(QApplication::translate("ImageViewerClass", "Blur", Q_NULLPTR));
        actionSharpen->setText(QApplication::translate("ImageViewerClass", "Sharpen", Q_NULLPTR));
        checkBox->setText(QApplication::translate("ImageViewerClass", "Keep Aspect Ratio", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ImageViewerClass", "Applied filters:", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("ImageViewerClass", "Blur", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("ImageViewerClass", "Sharpen", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("ImageViewerClass", "File", Q_NULLPTR));
        menuFilter->setTitle(QApplication::translate("ImageViewerClass", "Filter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageViewerClass: public Ui_ImageViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWER_H
