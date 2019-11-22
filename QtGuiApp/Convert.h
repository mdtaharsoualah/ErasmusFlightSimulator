#pragma once

#include <windows.h>
#include <tchar.h>

#include <iostream>

#include "UsbCan32.h"
#include <cstdint>
#include <cmath>

#include <qthread.h>
#include <qtimer.h>


#define ALTSHIFT 1500
#define VSPEEDSHIFT 4096
#define FIWED_POINT_FRACTIONAL_BITS_CAP 7
#define FIWED_POINT_FRACTIONAL_BITS_SPEED 3

#define FIWED_POINT_FRACTIONAL_BITS_DEG 13
#define FIWED_POINT_FRACTIONAL_BITS_RATE 9
#define DEGSHIFT 4
#define RATESHIFT 64

typedef uint16_t fixed_point_t;


class UsbCan : public QObject
{
	Q_OBJECT

public:

	
	void CanSend(BYTE Id,int type);



	void CanSend1(BYTE Id, double altitude, double cap, double vspeed, double hspeed);

	void CanSend2(BYTE Id, double PitchDeg, double PitchRat, double RollDeg, double RollRat);

	void CanReceive();

	void ResetData();

	void static PUBLIC AppConnectControlCallbackEx(DWORD dwEvent_p, DWORD dwParam_p, void * pArg_p);

	

	void static PUBLIC AppEventCallbackEx(tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void* pArg_p);

	void setreceiveBool(bool);

signals:
	void CanThrottle(double);
	void CanYoke(double, double);
	void CanConnected(bool);
	void CanDisconnected(bool);

public slots:
	void CanConnect();
	void CanDisconnect();

	void usbCanStart();

	void tmout();

	void SetAlt(double altitude);

	void SetCap(double cap);

	void SetVSpeed(double VSpeed);

	void SetHSpeed(double HSpeed);
	
	void SetPitchDeg(double value);
	void SetPitchRate(double value);
	void SetRollDeg(double value);
	void SetRollRate(double value);

private:
	UCANRET bRet;
	tUcanHandle UcanHandle;
	tUcanHardwareInfo HwInfo;
	_TCHAR szDeviceNr[24];
	tCanMsgStruct CanTxMsg, CanRxMsg;
	BYTE Tram1[8];
	BYTE Tram2[8];
	tUcanInitCanParam InitParam;
	bool receiveBool;
	bool timeout150;
	bool timeout301;
	int timeCount = 0;
	float throttleCan;
	float yokex;
	float yokey;

	DWORD dwRxCount;

	QTimer *timer10 = new QTimer(this);

};
