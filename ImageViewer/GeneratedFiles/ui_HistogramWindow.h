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
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QCheckBox *redCheckBox;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;

    void setupUi(QWidget *HistogramWindow)
    {
        if (HistogramWindow->objectName().isEmpty())
            HistogramWindow->setObjectName(QStringLiteral("HistogramWindow"));
        HistogramWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(HistogramWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new QGraphicsView(HistogramWindow);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        redCheckBox = new QCheckBox(HistogramWindow);
        redCheckBox->setObjectName(QStringLiteral("redCheckBox"));
        redCheckBox->setChecked(true);

        horizontalLayout->addWidget(redCheckBox);

        checkBox = new QCheckBox(HistogramWindow);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        horizontalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(HistogramWindow);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setChecked(true);

        horizontalLayout->addWidget(checkBox_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(HistogramWindow);

        QMetaObject::connectSlotsByName(HistogramWindow);
    } // setupUi

    void retranslateUi(QWidget *HistogramWindow)
    {
        HistogramWindow->setWindowTitle(QApplication::translate("HistogramWindow", "HistogramWindow", Q_NULLPTR));
        redCheckBox->setText(QApplication::translate("HistogramWindow", "Red", Q_NULLPTR));
        checkBox->setText(QApplication::translate("HistogramWindow", "Green", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("HistogramWindow", "Blue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HistogramWindow: public Ui_HistogramWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMWINDOW_H
