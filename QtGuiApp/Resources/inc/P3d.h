#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "SimConnect.h"
#include <strsafe.h>
#include "QueueClass.h"


#include <QObject>
#include <qtimer.h>
#include <qthread.h>

#include <sstream>

#include <QString>
#include <qtextedit.h>
#include <qslider.h>
#include <qcheckbox.h>
#include <qlcdnumber.h>
#include<QDebug>

#include "Convert.h"


enum GROUP_ID {
	GROUP_KEYS,
};
enum INPUT_ID {
	INPUT_KEYS,
};

enum EVENT_ID {
	EVENT_SIM_START,
};





class P3d : public QObject {
	Q_OBJECT

public:



	bool P3dConnect();
	void P3dDisconnect();
	
	void P3dConfig();



	static void DispatchCallback(SIMCONNECT_RECV *pData, DWORD cbData, void *pContext);
	void Process(SIMCONNECT_RECV *pData, DWORD cbData);
	void SetThrottle(double);

	void P3dRequestData();

	QueueClass Queue;

public slots:
	void start();
	void P3dStart();
	void AddElement(int id);
	void DelateElement(int id);
	void P3dSetThrottle(double value);
	void P3dSetYoke(double valueX,double valueY);

signals:
	void P3dPrintAltitude(double value);
	void P3dPrintCap(double value);
	void P3dPrintVSpeed(double value);
	void P3dPrintHSpeed(double value);
	void P3dPrintThrottle(double value);

	void P3dSetAltitude(double value);
	void P3dSetCap(double value);
	void P3dSetVSpeed(double value);
	void P3dSetHSpeed(double value);
	//void P3dSetThrottle(double value);


private:
	int quit = 0;
	HANDLE hSimConnect = NULL;
	double throttlePercent = 0;
	QThread* ThreadCan;
	UsbCan* usbcan;
};