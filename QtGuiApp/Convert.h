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
#define VSPEEDSHIFT 2048
#define FIWED_POINT_FRACTIONAL_BITS_CAP 7
#define FIWED_POINT_FRACTIONAL_BITS_SPEED 4

typedef uint16_t fixed_point_t;

struct DataTram1
{
	BYTE altitude[2];
	BYTE cap[2];
	BYTE VSpeed[2];
	BYTE HSpeed[2];
	DWORD Time;
};

class UsbCan : public QThread
{

protected:
	void run();

public:

	UsbCan(QObject *parent=0);

	void UsbCanConnect();
	void UsbCanDisconnect();
	void CanSend(BYTE Id,int type);



	void CanSend1(BYTE Id, double altitude, double cap, double vspeed, double hspeed);

	void CanSend2(BYTE Id, double altitude, double cap, double vspeed, double hspeed);

	void ResetData();

	void static PUBLIC AppConnectControlCallbackEx(DWORD dwEvent_p, DWORD dwParam_p, void * pArg_p);

	

	void static PUBLIC AppEventCallbackEx(tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void* pArg_p);

	void setreceiveBool(bool);



public slots:
	void start();
	void receive1(int Id, DataTram1 Data);

	void timeout10();

	void SetAlt(double altitude);

	void SetCap(double cap);

	void SetVSpeed(double VSpeed);

	void SetHSpeed(double HSpeed);

private:
	UCANRET bRet;
	tUcanHandle UcanHandle;
	tUcanHardwareInfo HwInfo;
	_TCHAR szDeviceNr[24];
	tCanMsgStruct CanMsg;
	DataTram1 Tram1;
	tUcanInitCanParam InitParam;
	bool receiveBool;
	bool timeout150;
	int timeCount = 0;

	QTimer* timer10;

};



