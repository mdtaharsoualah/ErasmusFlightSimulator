#pragma once

#include <windows.h>
#include <tchar.h>

#include <iostream>

#include "UsbCan32.h"
#include <cstdint>
#include <cmath>


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
};

class UsbCan
{
public:
	void UsbCanConnect();
	void UsbCanDisconnect();
	void CanSend1(BYTE Id);

	void SetAlt(double altitude);

	void SetCap(double cap);

	void SetVSpeed(double VSpeed);

	void SetHSpeed(double HSpeed);

	void ResetData();

	static void UcanCallbackFktEx(tUcanHandle UcanHandle_p, DWORD	dwEvent_p, BYTE	bChannel_p, void*pArg_p);

private:
	UCANRET bRet;
	tUcanHandle UcanHandle;
	tUcanHardwareInfo HwInfo;
	_TCHAR szDeviceNr[24];
	tCanMsgStruct CanMsg;
	DataTram1 Tram1;

};



