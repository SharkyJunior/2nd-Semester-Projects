/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *filterRegionButton;
    QLineEdit *regionLineEdit;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *chooseFileButton;
    QPushButton *loadDataButton;
    QPushButton *calcMetricsButton;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_2;
    QSpinBox *selectColumnSpinBox;
    QSpacerItem *horizontalSpacer;
    QTableWidget *dataTableWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QLineEdit *minValueOutputLine;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QLineEdit *maxValueOutputLine;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_5;
    QLineEdit *medianValueOutputLine;
    QSpacerItem *horizontalSpacer_8;
    QLabel *tableInfoLabel;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        filterRegionButton = new QPushButton(centralwidget);
        filterRegionButton->setObjectName("filterRegionButton");

        horizontalLayout_3->addWidget(filterRegionButton);

        regionLineEdit = new QLineEdit(centralwidget);
        regionLineEdit->setObjectName("regionLineEdit");
        regionLineEdit->setMaxLength(200);

        horizontalLayout_3->addWidget(regionLineEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        chooseFileButton = new QPushButton(centralwidget);
        chooseFileButton->setObjectName("chooseFileButton");

        horizontalLayout_2->addWidget(chooseFileButton);

        loadDataButton = new QPushButton(centralwidget);
        loadDataButton->setObjectName("loadDataButton");

        horizontalLayout_2->addWidget(loadDataButton);

        calcMetricsButton = new QPushButton(centralwidget);
        calcMetricsButton->setObjectName("calcMetricsButton");

        horizontalLayout_2->addWidget(calcMetricsButton);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        selectColumnSpinBox = new QSpinBox(centralwidget);
        selectColumnSpinBox->setObjectName("selectColumnSpinBox");
        selectColumnSpinBox->setMinimum(1);
        selectColumnSpinBox->setValue(1);

        horizontalLayout_4->addWidget(selectColumnSpinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        dataTableWidget = new QTableWidget(centralwidget);
        dataTableWidget->setObjectName("dataTableWidget");
        dataTableWidget->setEnabled(true);
        dataTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        dataTableWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        dataTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        dataTableWidget->horizontalHeader()->setStretchLastSection(false);
        dataTableWidget->verticalHeader()->setCascadingSectionResizes(false);
        dataTableWidget->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(dataTableWidget, 3, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setStrikeOut(false);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_6->setMargin(10);

        verticalLayout->addWidget(label_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout_5->addWidget(label_3);

        minValueOutputLine = new QLineEdit(centralwidget);
        minValueOutputLine->setObjectName("minValueOutputLine");
        minValueOutputLine->setReadOnly(true);

        horizontalLayout_5->addWidget(minValueOutputLine);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        maxValueOutputLine = new QLineEdit(centralwidget);
        maxValueOutputLine->setObjectName("maxValueOutputLine");
        maxValueOutputLine->setReadOnly(true);

        horizontalLayout_6->addWidget(maxValueOutputLine);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        horizontalLayout_7->addWidget(label_5);

        medianValueOutputLine = new QLineEdit(centralwidget);
        medianValueOutputLine->setObjectName("medianValueOutputLine");
        medianValueOutputLine->setReadOnly(true);

        horizontalLayout_7->addWidget(medianValueOutputLine);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_7);


        gridLayout->addLayout(verticalLayout, 5, 0, 1, 1);

        tableInfoLabel = new QLabel(centralwidget);
        tableInfoLabel->setObjectName("tableInfoLabel");
        tableInfoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(tableInfoLabel, 4, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CSV Reader", nullptr));
        filterRegionButton->setText(QCoreApplication::translate("MainWindow", "Filter region:", nullptr));
        chooseFileButton->setText(QCoreApplication::translate("MainWindow", "Choose file...", nullptr));
        loadDataButton->setText(QCoreApplication::translate("MainWindow", "Load data from file", nullptr));
        calcMetricsButton->setText(QCoreApplication::translate("MainWindow", "Calculate and Draw", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Select column for metrics:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Metrics", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Minimum Value", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Maximum Value", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Median", nullptr));
        tableInfoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
