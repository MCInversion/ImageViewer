/********************************************************************************
** Form generated from reading UI file 'HistogramWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMWINDOW_H
#define UI_HISTOGRAMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistogramWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *histogramView;
    QHBoxLayout *horizontalLayout;
    QCheckBox *redCheckBox;
    QCheckBox *greenCheckBox;
    QCheckBox *blueCheckBox;
    QVBoxLayout *progressBarLayout;

    void setupUi(QWidget *HistogramWindow)
    {
        if (HistogramWindow->objectName().isEmpty())
            HistogramWindow->setObjectName(QStringLiteral("HistogramWindow"));
        HistogramWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(HistogramWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        histogramView = new QGraphicsView(HistogramWindow);
        histogramView->setObjectName(QStringLiteral("histogramView"));

        verticalLayout->addWidget(histogramView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        redCheckBox = new QCheckBox(HistogramWindow);
        redCheckBox->setObjectName(QStringLiteral("redCheckBox"));
        redCheckBox->setChecked(true);

        horizontalLayout->addWidget(redCheckBox);

        greenCheckBox = new QCheckBox(HistogramWindow);
        greenCheckBox->setObjectName(QStringLiteral("greenCheckBox"));
        greenCheckBox->setChecked(true);

        horizontalLayout->addWidget(greenCheckBox);

        blueCheckBox = new QCheckBox(HistogramWindow);
        blueCheckBox->setObjectName(QStringLiteral("blueCheckBox"));
        blueCheckBox->setChecked(true);

        horizontalLayout->addWidget(blueCheckBox);


        verticalLayout->addLayout(horizontalLayout);

        progressBarLayout = new QVBoxLayout();
        progressBarLayout->setSpacing(6);
        progressBarLayout->setObjectName(QStringLiteral("progressBarLayout"));

        verticalLayout->addLayout(progressBarLayout);


        retranslateUi(HistogramWindow);
        QObject::connect(redCheckBox, SIGNAL(stateChanged(int)), HistogramWindow, SLOT(ActionReplot()));
        QObject::connect(greenCheckBox, SIGNAL(stateChanged(int)), HistogramWindow, SLOT(ActionReplot()));
        QObject::connect(blueCheckBox, SIGNAL(stateChanged(int)), HistogramWindow, SLOT(ActionReplot()));

        QMetaObject::connectSlotsByName(HistogramWindow);
    } // setupUi

    void retranslateUi(QWidget *HistogramWindow)
    {
        HistogramWindow->setWindowTitle(QApplication::translate("HistogramWindow", "HistogramWindow", Q_NULLPTR));
        redCheckBox->setText(QApplication::translate("HistogramWindow", "Red", Q_NULLPTR));
        greenCheckBox->setText(QApplication::translate("HistogramWindow", "Green", Q_NULLPTR));
        blueCheckBox->setText(QApplication::translate("HistogramWindow", "Blue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HistogramWindow: public Ui_HistogramWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMWINDOW_H
