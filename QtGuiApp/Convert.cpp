#include "Convert.h"

void UsbCan::setreceiveBool(bool value) {
	receiveBool = value;
}

void UsbCan::run() {
	timeCount = 0;
	timeout301 = false;
	timeout150 = false;
	UsbCanConnect();

	exec();
	
	
}

int UsbCan::exec()
{
	while (1) {
		if (receiveBool) {
			setreceiveBool(false);
			CanReceive();
		}
		if (timeout150) {
			timeout150 = false;
			CanSend(0x1, 1);
		}
		if (timeout301) {
			timeout301 = false;
			CanSend(0x2, 2);
		}
	}
	return 0;
}

void UsbCan::tmout() {
	timeCount++;
	if (timeCount == 5) {
		timeout150 = true;
		timeCount = 0;
	}
	if (timeCount == 3) {
		timeout301 = true;
	}
}


void UsbCan::UsbCanConnect() {
	
	// initialize USB-CANmodul
	//bRet = UcanInitHardware(&UcanHandle, USBCAN_ANY_MODULE, NULL);


	setreceiveBool(false);

	memset(&InitParam, 0, sizeof(InitParam));
	InitParam.m_dwSize = sizeof(InitParam);
	InitParam.m_bMode = kUcanModeNormal;
	InitParam.m_bBTR0 = HIBYTE(USBCAN_BAUDEX_250kBit);
	InitParam.m_bBTR1 = LOBYTE(USBCAN_BAUDEX_250kBit);
	InitParam.m_bOCR = USBCAN_OCR_DEFAULT;
	InitParam.m_dwAMR = USBCAN_AMR_ALL;
	InitParam.m_dwACR = USBCAN_ACR_ALL;
	InitParam.m_dwBaudrate = USBCAN_BAUDEX_250kBit;

	ResetData();

	CanTxMsg.m_bFF = 0;
	CanTxMsg.m_bDLC = 8;

	bRet = UcanInitHwConnectControlEx(AppConnectControlCallbackEx, NULL);

	if (bRet == USBCAN_SUCCESSFUL)
	{
		bRet = UcanInitHardwareEx(&UcanHandle, USBCAN_ANY_MODULE,
			AppEventCallbackEx, this);

		bRet = UcanInitCanEx2(UcanHandle, USBCAN_CHANNEL_CH0,
			&InitParam);
	}
}

void PUBLIC UsbCan::AppConnectControlCallbackEx(DWORD dwEvent_p, DWORD dwParam_p, void* pArg_p)
{
	switch (dwEvent_p)
	{
	case USBCAN_EVENT_CONNECT:
		qDebug("connect!!");
		break;
	case USBCAN_EVENT_DISCONNECT:
		qDebug("disconnect!!");
		break;
	}
}


void PUBLIC UsbCan::AppEventCallbackEx(tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void* pArg_p){
	
	UsbCan *pThis = reinterpret_cast<UsbCan*>(pArg_p);

	switch (dwEvent_p)
	{

	case USBCAN_EVENT_RECEIVE: // CAN message received
		pThis->setreceiveBool(true);
		break;

	case USBCAN_EVENT_STATUS: // changes error status
	// signal that the CAN status can be read SetEvent(ahWaitHandles_g[STATUS]);
		break;

	}

}

void UsbCan::UsbCanDisconnect() {

}

void UsbCan::CanSend(BYTE Id, int type) {
	
	CanTxMsg.m_dwID = Id;
	BYTE *TmpData;
	
	if (type == 1) {
		BYTE Tmp[8] = { Tram1.altitude[0],Tram1.altitude[1], Tram1.cap[0], Tram1.cap[1], Tram1.VSpeed[0], Tram1.VSpeed[1], Tram1.HSpeed[0], Tram1.HSpeed[1] };
		TmpData = Tmp;
	}
	else if (type == 2) {
		BYTE Tmp2[8] = { Tram2.PitchDeg[0],Tram2.PitchDeg[1], Tram2.PitchRate[0], Tram2.PitchRate[1], Tram2.RollDeg[0], Tram2.RollDeg[1], Tram2.RollRate[0], Tram2.RollRate[1] };
		TmpData = Tmp2;
	}
	
	memcpy(CanTxMsg.m_bData,TmpData, 8);
	UcanWriteCanMsg(UcanHandle, &CanTxMsg);
}


void UsbCan::SetAlt(double altitude) {
	unsigned int alt = (unsigned int)(altitude + ALTSHIFT);
	memcpy(Tram1.altitude, &alt, sizeof(int));
}

void UsbCan::SetCap(double cap)
{
	fixed_point_t tmp = (fixed_point_t) round(cap * (1 << FIWED_POINT_FRACTIONAL_BITS_CAP));
	memcpy(Tram1.cap, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetVSpeed(double VSpeed) {
	double tmpVal = VSpeed + VSPEEDSHIFT;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_SPEED));
	memcpy(Tram1.VSpeed, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetHSpeed(double HSpeed) {
	fixed_point_t tmp = (fixed_point_t)round(HSpeed * (1 << FIWED_POINT_FRACTIONAL_BITS_SPEED));
	memcpy(Tram1.HSpeed, &tmp, sizeof(fixed_point_t));
}


void UsbCan::SetPitchDeg(double VSpeed) {
	double tmpVal = VSpeed + DEGSHIFT;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_DEG));
	memcpy(Tram2.PitchDeg, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetPitchRate(double HSpeed) {
	double tmpVal = HSpeed + 64;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_RATE));
	memcpy(Tram2.PitchRate, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetRollDeg(double VSpeed) {
	double tmpVal = VSpeed + DEGSHIFT;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_DEG));
	memcpy(Tram2.RollDeg, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetRollRate(double HSpeed) {
	double tmpVal = HSpeed + 64;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_RATE));
	memcpy(Tram2.RollRate, &tmp, sizeof(fixed_point_t));
}


void UsbCan::CanSend1(BYTE Id, double altitude, double cap, double vspeed, double hspeed)
{
	SetAlt(altitude);
	SetCap(cap);
	SetVSpeed(vspeed);
	SetHSpeed(hspeed);
	CanSend(Id,1);
}

void UsbCan::CanSend2(BYTE Id, double PitchDeg, double PitchRat, double RollDeg, double RollRat)
{
	SetPitchDeg(PitchDeg);
	SetPitchRate(PitchRat);
	SetRollDeg(RollDeg);
	SetRollRate(RollRat);
	CanSend(Id, 2);
}

void UsbCan::ResetData()
{
	for (int i = 0; i < 2; i++)
	{
		Tram1.altitude[i] = 0x0;
		Tram1.cap[i] = 0x00;
		Tram1.VSpeed[i] = 0x0;
		Tram1.HSpeed[i] = 0x0;
		Tram2.PitchDeg[i] = 0x0;
		Tram2.PitchRate[i] = 0x0;
		Tram2.RollDeg[i] = 0x0;
		Tram2.RollRate[i] = 0x0;
	}
}

void UsbCan::CanReceive()
{
	dwRxCount = 100;
	bRet = UcanReadCanMsg(UcanHandle, &CanRxMsg);
	if (CanRxMsg.m_dwID == 0x11)
		emit CanThrottle(CanRxMsg.m_bData[0]);
	if (CanRxMsg.m_dwID == 0x12) {
		float yokex;
		float yokey;
		memcpy(&yokex, CanRxMsg.m_bData, 4);
		memcpy(&yokey, (&CanRxMsg.m_bData)[4], 4);
		emit CanYoke(yokex, yokey);
	}
}

void UsbCan::receive1(int Id, DataTram1 Data) {

}