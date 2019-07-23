#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApp.h"
#include <qtimer.h>
#include "P3d.h"
#include "QueueClass.h"



class QtGuiApp : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApp(QWidget *parent = Q_NULLPTR);
private slots:
	void printData();
	void on_CheckAltitude_stateChanged(int arg1);
	void on_CheckCap_stateChanged(int arg1);
	void on_CheckVSpeed_stateChanged(int arg1);
	void on_CheckHSpeed_stateChanged(int arg1);
	void on_CheckThrottle_stateChanged(int arg1);
	void on_ControlThrottle_valueChanged(int value);
	void on_MbedReadButton_clicked();
private:
	Ui::QtGuiAppClass ui;
	int i = 0;
	P3d p3d;
};
