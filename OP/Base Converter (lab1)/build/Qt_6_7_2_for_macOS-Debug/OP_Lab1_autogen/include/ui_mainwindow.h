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
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *inputLineEdit;
    QVBoxLayout *verticalLayout;
    QLabel *fromLabel;
    QRadioButton *fromDecRadioButton;
    QRadioButton *fromBinRadioButton;
    QRadioButton *fromOctRadioButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *toLabel;
    QRadioButton *toDecRadioButton;
    QRadioButton *toBinRadioButton;
    QRadioButton *toOctRadioButton;
    QLineEdit *outputLineEdit;
    QLabel *statusLabel;
    QPushButton *convertButton;
    QPushButton *swapButton;
    QPushButton *copyButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *fromRadioButtonGroup;
    QButtonGroup *toRadioButtonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(688, 303);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        inputLineEdit = new QLineEdit(centralwidget);
        inputLineEdit->setObjectName("inputLineEdit");
        inputLineEdit->setMaximumSize(QSize(150, 16777215));
        inputLineEdit->setMaxLength(40);

        horizontalLayout->addWidget(inputLineEdit);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        fromLabel = new QLabel(centralwidget);
        fromLabel->setObjectName("fromLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fromLabel->sizePolicy().hasHeightForWidth());
        fromLabel->setSizePolicy(sizePolicy);
        fromLabel->setMaximumSize(QSize(16777215, 50));
        fromLabel->setBaseSize(QSize(0, 0));

        verticalLayout->addWidget(fromLabel);

        fromDecRadioButton = new QRadioButton(centralwidget);
        fromRadioButtonGroup = new QButtonGroup(MainWindow);
        fromRadioButtonGroup->setObjectName("fromRadioButtonGroup");
        fromRadioButtonGroup->addButton(fromDecRadioButton);
        fromDecRadioButton->setObjectName("fromDecRadioButton");
        fromDecRadioButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        fromDecRadioButton->setChecked(true);

        verticalLayout->addWidget(fromDecRadioButton);

        fromBinRadioButton = new QRadioButton(centralwidget);
        fromRadioButtonGroup->addButton(fromBinRadioButton);
        fromBinRadioButton->setObjectName("fromBinRadioButton");
        fromBinRadioButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout->addWidget(fromBinRadioButton);

        fromOctRadioButton = new QRadioButton(centralwidget);
        fromRadioButtonGroup->addButton(fromOctRadioButton);
        fromOctRadioButton->setObjectName("fromOctRadioButton");
        fromOctRadioButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout->addWidget(fromOctRadioButton);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        toLabel = new QLabel(centralwidget);
        toLabel->setObjectName("toLabel");

        verticalLayout_2->addWidget(toLabel);

        toDecRadioButton = new QRadioButton(centralwidget);
        toRadioButtonGroup = new QButtonGroup(MainWindow);
        toRadioButtonGroup->setObjectName("toRadioButtonGroup");
        toRadioButtonGroup->addButton(toDecRadioButton);
        toDecRadioButton->setObjectName("toDecRadioButton");

        verticalLayout_2->addWidget(toDecRadioButton);

        toBinRadioButton = new QRadioButton(centralwidget);
        toRadioButtonGroup->addButton(toBinRadioButton);
        toBinRadioButton->setObjectName("toBinRadioButton");
        toBinRadioButton->setChecked(true);

        verticalLayout_2->addWidget(toBinRadioButton);

        toOctRadioButton = new QRadioButton(centralwidget);
        toRadioButtonGroup->addButton(toOctRadioButton);
        toOctRadioButton->setObjectName("toOctRadioButton");

        verticalLayout_2->addWidget(toOctRadioButton);


        horizontalLayout->addLayout(verticalLayout_2);

        outputLineEdit = new QLineEdit(centralwidget);
        outputLineEdit->setObjectName("outputLineEdit");
        outputLineEdit->setMaximumSize(QSize(300, 16777215));
        outputLineEdit->setMaxLength(40);
        outputLineEdit->setReadOnly(true);

        horizontalLayout->addWidget(outputLineEdit);


        verticalLayout_3->addLayout(horizontalLayout);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout_3->addWidget(statusLabel);

        convertButton = new QPushButton(centralwidget);
        convertButton->setObjectName("convertButton");
        convertButton->setCheckable(false);

        verticalLayout_3->addWidget(convertButton);

        swapButton = new QPushButton(centralwidget);
        swapButton->setObjectName("swapButton");

        verticalLayout_3->addWidget(swapButton);

        copyButton = new QPushButton(centralwidget);
        copyButton->setObjectName("copyButton");

        verticalLayout_3->addWidget(copyButton);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 688, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Converter", nullptr));
        fromLabel->setText(QCoreApplication::translate("MainWindow", "From", nullptr));
        fromDecRadioButton->setText(QCoreApplication::translate("MainWindow", "DEC", nullptr));
        fromBinRadioButton->setText(QCoreApplication::translate("MainWindow", "BIN", nullptr));
        fromOctRadioButton->setText(QCoreApplication::translate("MainWindow", "OCT", nullptr));
        toLabel->setText(QCoreApplication::translate("MainWindow", "To", nullptr));
        toDecRadioButton->setText(QCoreApplication::translate("MainWindow", "DEC", nullptr));
        toBinRadioButton->setText(QCoreApplication::translate("MainWindow", "BIN", nullptr));
        toOctRadioButton->setText(QCoreApplication::translate("MainWindow", "OCT", nullptr));
        statusLabel->setText(QString());
        convertButton->setText(QCoreApplication::translate("MainWindow", "Convert", nullptr));
        swapButton->setText(QCoreApplication::translate("MainWindow", "Swap", nullptr));
        copyButton->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
