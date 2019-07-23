/********************************************************************************
** Form generated from reading UI file 'QtGuiApp.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIAPP_H
#define UI_QTGUIAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiAppClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QLCDNumber *LcdAltitude;
    QCheckBox *CheckAltitude;
    QGroupBox *groupBox_3;
    QLCDNumber *LcdCap;
    QCheckBox *CheckCap;
    QGroupBox *groupBox_4;
    QLCDNumber *LcdVSpeed;
    QCheckBox *CheckVSpeed;
    QGroupBox *groupBox_5;
    QLCDNumber *LcdHSpeed;
    QCheckBox *CheckHSpeed;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QLCDNumber *LcdThrottle;
    QCheckBox *CheckThrottle;
    QSlider *ControlThrottle;
    QWidget *tab_3;
    QPushButton *MbedReadButton;
    QTextEdit *TextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiAppClass)
    {
        if (QtGuiAppClass->objectName().isEmpty())
            QtGuiAppClass->setObjectName(QString::fromUtf8("QtGuiAppClass"));
        QtGuiAppClass->setEnabled(true);
        QtGuiAppClass->resize(620, 400);
        centralWidget = new QWidget(QtGuiAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        LcdAltitude = new QLCDNumber(groupBox);
        LcdAltitude->setObjectName(QString::fromUtf8("LcdAltitude"));
        LcdAltitude->setGeometry(QRect(270, 20, 320, 30));
        CheckAltitude = new QCheckBox(groupBox);
        CheckAltitude->setObjectName(QString::fromUtf8("CheckAltitude"));
        CheckAltitude->setGeometry(QRect(10, 25, 200, 20));

        verticalLayout_2->addWidget(groupBox);

        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        LcdCap = new QLCDNumber(groupBox_3);
        LcdCap->setObjectName(QString::fromUtf8("LcdCap"));
        LcdCap->setGeometry(QRect(270, 20, 320, 30));
        CheckCap = new QCheckBox(groupBox_3);
        CheckCap->setObjectName(QString::fromUtf8("CheckCap"));
        CheckCap->setGeometry(QRect(10, 25, 200, 20));

        verticalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        LcdVSpeed = new QLCDNumber(groupBox_4);
        LcdVSpeed->setObjectName(QString::fromUtf8("LcdVSpeed"));
        LcdVSpeed->setGeometry(QRect(270, 20, 320, 30));
        CheckVSpeed = new QCheckBox(groupBox_4);
        CheckVSpeed->setObjectName(QString::fromUtf8("CheckVSpeed"));
        CheckVSpeed->setGeometry(QRect(10, 25, 200, 20));

        verticalLayout_2->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        LcdHSpeed = new QLCDNumber(groupBox_5);
        LcdHSpeed->setObjectName(QString::fromUtf8("LcdHSpeed"));
        LcdHSpeed->setGeometry(QRect(270, 20, 320, 30));
        CheckHSpeed = new QCheckBox(groupBox_5);
        CheckHSpeed->setObjectName(QString::fromUtf8("CheckHSpeed"));
        CheckHSpeed->setGeometry(QRect(10, 25, 200, 20));

        verticalLayout_2->addWidget(groupBox_5);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        LcdThrottle = new QLCDNumber(groupBox_2);
        LcdThrottle->setObjectName(QString::fromUtf8("LcdThrottle"));
        LcdThrottle->setGeometry(QRect(270, 20, 320, 30));
        CheckThrottle = new QCheckBox(groupBox_2);
        CheckThrottle->setObjectName(QString::fromUtf8("CheckThrottle"));
        CheckThrottle->setGeometry(QRect(10, 25, 200, 20));
        ControlThrottle = new QSlider(groupBox_2);
        ControlThrottle->setObjectName(QString::fromUtf8("ControlThrottle"));
        ControlThrottle->setGeometry(QRect(10, 60, 580, 25));
        ControlThrottle->setMaximum(100);
        ControlThrottle->setSingleStep(1);
        ControlThrottle->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(groupBox_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        MbedReadButton = new QPushButton(tab_3);
        MbedReadButton->setObjectName(QString::fromUtf8("MbedReadButton"));
        MbedReadButton->setGeometry(QRect(0, 10, 602, 23));
        TextEdit = new QTextEdit(tab_3);
        TextEdit->setObjectName(QString::fromUtf8("TextEdit"));
        TextEdit->setGeometry(QRect(0, 40, 602, 150));
        TextEdit->setMaximumSize(QSize(16777215, 150));
        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);

        QtGuiAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGuiAppClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 620, 21));
        QtGuiAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiAppClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtGuiAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiAppClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtGuiAppClass->setStatusBar(statusBar);

        retranslateUi(QtGuiAppClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QtGuiAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiAppClass)
    {
        QtGuiAppClass->setWindowTitle(QCoreApplication::translate("QtGuiAppClass", "QtGuiApp", nullptr));
        groupBox->setTitle(QCoreApplication::translate("QtGuiAppClass", "Altitude", nullptr));
        CheckAltitude->setText(QCoreApplication::translate("QtGuiAppClass", "Altitude", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("QtGuiAppClass", "Cap", nullptr));
        CheckCap->setText(QCoreApplication::translate("QtGuiAppClass", "Cap", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("QtGuiAppClass", "V-Speed", nullptr));
        CheckVSpeed->setText(QCoreApplication::translate("QtGuiAppClass", "V Speed", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("QtGuiAppClass", "H-Speed", nullptr));
        CheckHSpeed->setText(QCoreApplication::translate("QtGuiAppClass", "H Speed", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("QtGuiAppClass", "Tab 1", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("QtGuiAppClass", "Throttle", nullptr));
        CheckThrottle->setText(QCoreApplication::translate("QtGuiAppClass", "Throttle", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("QtGuiAppClass", "Tab 2", nullptr));
        MbedReadButton->setText(QCoreApplication::translate("QtGuiAppClass", "Mbed Read", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("QtGuiAppClass", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiAppClass: public Ui_QtGuiAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPP_H
