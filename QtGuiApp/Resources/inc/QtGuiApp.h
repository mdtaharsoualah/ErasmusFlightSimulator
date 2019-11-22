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
	void DeleteElement(int id);
	void SetAltitude(double value);
	void P3dConnect();
	void P3dDisconnect();
	void CanConnect();
	void CanDisconnect();

public slots:
	void on_P3dConnectButton_clicked();
	void on_CanConnectButton_clicked();

	void P3dConnected(bool);
	void P3dDisconnected(bool);

	void CanConnected(bool);
	void CanDisconnected(bool);

	void on_Tram1Check_stateChanged(int arg);
	
	void on_Tram2Check_stateChanged(int arg1);

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
	bool P3dConnectStat = false;
	bool CanConnectStat = false;
};
