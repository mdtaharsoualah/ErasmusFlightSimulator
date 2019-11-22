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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QWidget *tab_1;
    QVBoxLayout *verticalLayout_4;
    QPushButton *P3dConnectButton;
    QPushButton *CanConnectButton;
    QTextEdit *TextEdit;
    QWidget *tab;
    QFormLayout *formLayout;
    QLabel *label;
    QLCDNumber *LcdAltitude;
    QLabel *label_2;
    QLCDNumber *LcdCap;
    QLabel *label_3;
    QLCDNumber *LcdVSpeed;
    QLabel *label_4;
    QLCDNumber *LcdHSpeed;
    QCheckBox *Tram1Check;
    QWidget *tab_2;
    QFormLayout *formLayout_2;
    QLCDNumber *LcdPitchDeg;
    QLCDNumber *LcdPitchRate;
    QLCDNumber *LcdRollDeg;
    QLCDNumber *LcdRollRate;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QCheckBox *Tram2Check;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiAppClass)
    {
        if (QtGuiAppClass->objectName().isEmpty())
            QtGuiAppClass->setObjectName(QString::fromUtf8("QtGuiAppClass"));
        QtGuiAppClass->setEnabled(true);
        QtGuiAppClass->resize(471, 337);
        centralWidget = new QWidget(QtGuiAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        verticalLayout_4 = new QVBoxLayout(tab_1);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        P3dConnectButton = new QPushButton(tab_1);
        P3dConnectButton->setObjectName(QString::fromUtf8("P3dConnectButton"));

        verticalLayout_4->addWidget(P3dConnectButton);

        CanConnectButton = new QPushButton(tab_1);
        CanConnectButton->setObjectName(QString::fromUtf8("CanConnectButton"));

        verticalLayout_4->addWidget(CanConnectButton);

        TextEdit = new QTextEdit(tab_1);
        TextEdit->setObjectName(QString::fromUtf8("TextEdit"));
        TextEdit->setMaximumSize(QSize(16777215, 150));

        verticalLayout_4->addWidget(TextEdit);

        tabWidget->addTab(tab_1, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        formLayout = new QFormLayout(tab);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(150, 0));
        QFont font;
        font.setPointSize(25);
        label->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        LcdAltitude = new QLCDNumber(tab);
        LcdAltitude->setObjectName(QString::fromUtf8("LcdAltitude"));

        formLayout->setWidget(2, QFormLayout::FieldRole, LcdAltitude);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        LcdCap = new QLCDNumber(tab);
        LcdCap->setObjectName(QString::fromUtf8("LcdCap"));

        formLayout->setWidget(3, QFormLayout::FieldRole, LcdCap);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_3);

        LcdVSpeed = new QLCDNumber(tab);
        LcdVSpeed->setObjectName(QString::fromUtf8("LcdVSpeed"));

        formLayout->setWidget(4, QFormLayout::FieldRole, LcdVSpeed);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        formLayout->setWidget(5, QFormLayout::LabelRole, label_4);

        LcdHSpeed = new QLCDNumber(tab);
        LcdHSpeed->setObjectName(QString::fromUtf8("LcdHSpeed"));

        formLayout->setWidget(5, QFormLayout::FieldRole, LcdHSpeed);

        Tram1Check = new QCheckBox(tab);
        Tram1Check->setObjectName(QString::fromUtf8("Tram1Check"));
        QFont font1;
        font1.setPointSize(16);
        Tram1Check->setFont(font1);

        formLayout->setWidget(0, QFormLayout::FieldRole, Tram1Check);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        formLayout_2 = new QFormLayout(tab_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        LcdPitchDeg = new QLCDNumber(tab_2);
        LcdPitchDeg->setObjectName(QString::fromUtf8("LcdPitchDeg"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, LcdPitchDeg);

        LcdPitchRate = new QLCDNumber(tab_2);
        LcdPitchRate->setObjectName(QString::fromUtf8("LcdPitchRate"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, LcdPitchRate);

        LcdRollDeg = new QLCDNumber(tab_2);
        LcdRollDeg->setObjectName(QString::fromUtf8("LcdRollDeg"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, LcdRollDeg);

        LcdRollRate = new QLCDNumber(tab_2);
        LcdRollRate->setObjectName(QString::fromUtf8("LcdRollRate"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, LcdRollRate);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(150, 0));
        label_5->setFont(font);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(150, 0));
        label_6->setFont(font);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(150, 0));
        label_7->setFont(font);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(150, 0));
        label_8->setFont(font);

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_8);

        Tram2Check = new QCheckBox(tab_2);
        Tram2Check->setObjectName(QString::fromUtf8("Tram2Check"));
        Tram2Check->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, Tram2Check);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        QtGuiAppClass->setCentralWidget(centralWidget);
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
        P3dConnectButton->setText(QCoreApplication::translate("QtGuiAppClass", "P3d Connect", nullptr));
        CanConnectButton->setText(QCoreApplication::translate("QtGuiAppClass", "Usb-Can Connect", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("QtGuiAppClass", "Acceuil", nullptr));
        label->setText(QCoreApplication::translate("QtGuiAppClass", "Altitude", nullptr));
        label_2->setText(QCoreApplication::translate("QtGuiAppClass", "CAP", nullptr));
        label_3->setText(QCoreApplication::translate("QtGuiAppClass", "VSpeed", nullptr));
        label_4->setText(QCoreApplication::translate("QtGuiAppClass", "HSpeed", nullptr));
        Tram1Check->setText(QCoreApplication::translate("QtGuiAppClass", "Tram1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("QtGuiAppClass", "Tram1", nullptr));
        label_5->setText(QCoreApplication::translate("QtGuiAppClass", "Pitch Deg", nullptr));
        label_6->setText(QCoreApplication::translate("QtGuiAppClass", "Pitch Rate", nullptr));
        label_7->setText(QCoreApplication::translate("QtGuiAppClass", "Roll Deg", nullptr));
        label_8->setText(QCoreApplication::translate("QtGuiAppClass", "Roll Rate", nullptr));
        Tram2Check->setText(QCoreApplication::translate("QtGuiAppClass", "Tram2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("QtGuiAppClass", "Tram2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiAppClass: public Ui_QtGuiAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPP_H
