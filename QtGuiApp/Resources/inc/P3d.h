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

	
	
	void P3dConfig();

	static void DispatchCallback(SIMCONNECT_RECV *pData, DWORD cbData, void *pContext);
	void Process(SIMCONNECT_RECV *pData, DWORD cbData);

	void P3dRequestData();
	

public slots:
	void P3dConnect();
	void P3dDisconnect();
	void P3dBoucle();
	void P3dstart();
	void AddElement(int id);
	void DeleteElement(int id);
	void P3dSetThrottle(double value);
	void P3dSetYoke(double valueX,double valueY);

signals:
	void P3dConnected(bool);
	void P3dDisconnected(bool);
	void P3dAltitude(double value);
	void P3dCap(double value);
	void P3dVSpeed(double value);
	void P3dHSpeed(double value);

	void P3dPitchDeg(double value);
	void P3dPitchRate(double value);
	void P3dRollDeg(double value);
	void P3dRollRate(double value);


private:
	HANDLE m_hSimConnect = NULL;

	double m_throttle;
	double m_yokeX;
	double m_yokeY;

	UsbCan *usbcan;

	std::vector<int> m_IdDefinition;
	std::mutex m_IdDefinitionMutex;

	QTimer *timer = new QTimer(this);
};