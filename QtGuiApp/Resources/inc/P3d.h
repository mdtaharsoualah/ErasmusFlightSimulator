#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "SimConnect.h"
#include <strsafe.h>
#include "QueueClass.h"


#include <sstream>

#include <QString>
#include <qtextedit.h>
#include <qslider.h>
#include <qcheckbox.h>
#include <qlcdnumber.h>
#include<QDebug>

#include "Convert.h"

struct QtParameter
{
	//Affichage
	QTextEdit* TextEdit;
	//Altitude
	QCheckBox* CheckAltitude;
	QLCDNumber* LcdAltitude;
	//Cap
	QCheckBox* CheckCap;
	QLCDNumber* LcdCap;
	//VSpeed
	QCheckBox* CheckVSpeed;
	QLCDNumber* LcdVSpeed;
	//HSpeed
	QCheckBox* CheckHSpeed;
	QLCDNumber* LcdHSpeed;
	//Throttle
	QCheckBox* CheckThrottle;
	QLCDNumber* LcdThrottle;
	QSlider* ControlThrottle;
};


enum GROUP_ID {
	GROUP_KEYS,
};
enum INPUT_ID {
	INPUT_KEYS,
};

enum EVENT_ID {
	EVENT_SIM_START,
};





class P3d
{
public:



	bool P3dConnect();
	void P3dDisconnect();
	void P3dStart();

	void P3dConfig();
	void P3dConfig(QtParameter*);

	void P3dPrintData();


	static void DispatchCallback(SIMCONNECT_RECV *pData, DWORD cbData, void *pContext);


	void Process(SIMCONNECT_RECV *pData, DWORD cbData);
	void P3dPrintAltitude(double value);
	void P3dPrintCap(double value);
	void P3dPrintVSpeed(double value);
	void P3dPrintHSpeed(double value);
	void P3dPrintThrottle(double value);
	void SetThrottle(double);

	void P3dRequestData();
	
	QueueClass Queue;

private:
	int quit = 0;
	HANDLE hSimConnect = NULL;
	QtParameter QtParametre;
	double throttlePercent = 0;
	UsbCan usbcan;

};