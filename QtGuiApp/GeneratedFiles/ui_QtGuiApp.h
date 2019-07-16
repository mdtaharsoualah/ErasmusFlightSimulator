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
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiAppClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLCDNumber *LcdAltitude;
    QCheckBox *CheckAltitude;
    QTextEdit *TextEdit;
    QGroupBox *groupBox_2;
    QLCDNumber *LcdThrottle;
    QCheckBox *CheckThrottle;
    QSlider *ControlThrottle;
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
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 600, 60));
        LcdAltitude = new QLCDNumber(groupBox);
        LcdAltitude->setObjectName(QString::fromUtf8("LcdAltitude"));
        LcdAltitude->setGeometry(QRect(270, 20, 320, 30));
        CheckAltitude = new QCheckBox(groupBox);
        CheckAltitude->setObjectName(QString::fromUtf8("CheckAltitude"));
        CheckAltitude->setGeometry(QRect(10, 25, 200, 20));
        TextEdit = new QTextEdit(centralWidget);
        TextEdit->setObjectName(QString::fromUtf8("TextEdit"));
        TextEdit->setGeometry(QRect(10, 180, 600, 160));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 80, 600, 90));
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

        QMetaObject::connectSlotsByName(QtGuiAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiAppClass)
    {
        QtGuiAppClass->setWindowTitle(QCoreApplication::translate("QtGuiAppClass", "QtGuiApp", nullptr));
        groupBox->setTitle(QCoreApplication::translate("QtGuiAppClass", "Altitude", nullptr));
        CheckAltitude->setText(QCoreApplication::translate("QtGuiAppClass", "Altitude", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("QtGuiAppClass", "Throttle", nullptr));
        CheckThrottle->setText(QCoreApplication::translate("QtGuiAppClass", "Throttle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiAppClass: public Ui_QtGuiAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPP_H
