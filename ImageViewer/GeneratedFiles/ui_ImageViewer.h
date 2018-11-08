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
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
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
    QCheckBox *blurCheckBox;
    QCheckBox *sharpenCheckBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *radiusSlider;
    QLabel *radiusLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSlider *amountSlider;
    QLabel *amountLabel;
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
        blurCheckBox = new QCheckBox(verticalLayoutWidget);
        blurCheckBox->setObjectName(QStringLiteral("blurCheckBox"));

        verticalLayout_2->addWidget(blurCheckBox);

        sharpenCheckBox = new QCheckBox(verticalLayoutWidget);
        sharpenCheckBox->setObjectName(QStringLiteral("sharpenCheckBox"));

        verticalLayout_2->addWidget(sharpenCheckBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        radiusSlider = new QSlider(verticalLayoutWidget);
        radiusSlider->setObjectName(QStringLiteral("radiusSlider"));
        radiusSlider->setMaximum(300);
        radiusSlider->setValue(10);
        radiusSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(radiusSlider);

        radiusLabel = new QLabel(verticalLayoutWidget);
        radiusLabel->setObjectName(QStringLiteral("radiusLabel"));

        horizontalLayout->addWidget(radiusLabel);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        amountSlider = new QSlider(verticalLayoutWidget);
        amountSlider->setObjectName(QStringLiteral("amountSlider"));
        amountSlider->setEnabled(true);
        amountSlider->setMaximum(100);
        amountSlider->setValue(10);
        amountSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(amountSlider);

        amountLabel = new QLabel(verticalLayoutWidget);
        amountLabel->setObjectName(QStringLiteral("amountLabel"));

        horizontalLayout_3->addWidget(amountLabel);


        verticalLayout_2->addLayout(horizontalLayout_3);


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
        QObject::connect(actionBlur, SIGNAL(triggered()), ImageViewerClass, SLOT(ActionBlur()));
        QObject::connect(radiusSlider, SIGNAL(sliderMoved(int)), ImageViewerClass, SLOT(ActionChangeRadius()));
        QObject::connect(actionSharpen, SIGNAL(triggered()), ImageViewerClass, SLOT(ActionSharpen()));
        QObject::connect(amountSlider, SIGNAL(sliderMoved(int)), ImageViewerClass, SLOT(ActionChangeAmount()));
        QObject::connect(blurCheckBox, SIGNAL(stateChanged(int)), ImageViewerClass, SLOT(ActionDisplayBlurred()));
        QObject::connect(sharpenCheckBox, SIGNAL(stateChanged(int)), ImageViewerClass, SLOT(ActionDisplaySharpened()));

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
        blurCheckBox->setText(QApplication::translate("ImageViewerClass", "Blur", Q_NULLPTR));
        sharpenCheckBox->setText(QApplication::translate("ImageViewerClass", "Sharpen", Q_NULLPTR));
        label->setText(QApplication::translate("ImageViewerClass", "radius: ", Q_NULLPTR));
        radiusLabel->setText(QApplication::translate("ImageViewerClass", "10 px", Q_NULLPTR));
        label_3->setText(QApplication::translate("ImageViewerClass", "amount: ", Q_NULLPTR));
        amountLabel->setText(QApplication::translate("ImageViewerClass", "10 %", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("ImageViewerClass", "File", Q_NULLPTR));
        menuFilter->setTitle(QApplication::translate("ImageViewerClass", "Filter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageViewerClass: public Ui_ImageViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWER_H
