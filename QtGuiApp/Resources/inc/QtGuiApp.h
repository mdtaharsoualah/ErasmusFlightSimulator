#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApp.h"
#include <qtimer.h>
#include "P3d.h"
#include "QueueClass.h"
#include "convert.h"



class QtGuiApp : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApp(QWidget *parent = Q_NULLPTR);

signals:
	void AddElement(int id);
	void DelateElement(int id);
	void SetAltitude(double value);
private slots:
	void printData();
	void on_CheckAltitude_stateChanged(int arg1);
	void on_CheckCap_stateChanged(int arg1);
	void on_CheckVSpeed_stateChanged(int arg1);
	void on_CheckHSpeed_stateChanged(int arg1);
	
	void on_CheckPitchDeg_stateChanged(int arg1);
	void on_CheckPitchRate_stateChanged(int arg1);
	void on_CheckRollDeg_stateChanged(int arg1);
	void on_CheckRollRate_stateChanged(int arg1);

	void PrintAltitude(double value);
	void PrintCap(double value);
	void PrintVSpeed(double value);
	void PrintHSpeed(double value);
	void PrintPitchDeg(double value);
	void PrintPitchRate(double value);
	void PrintRollDeg(double value);
	void PrintRollRate(double value);

private:
	Ui::QtGuiAppClass ui;
	int i = 0;
	P3d p3d;
};
