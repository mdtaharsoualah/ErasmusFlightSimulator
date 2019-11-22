#include "Convert.h"

void UsbCan::setreceiveBool(bool value) {
	receiveBool = value;
}

void UsbCan::usbCanStart() {
	timeCount = 0;
	timeout301 = false;
	timeout150 = false;
	QObject::connect(timer10, SIGNAL(timeout()), this, SLOT(tmout()), Qt::QueuedConnection);
}


void UsbCan::tmout() {
	timeCount++;
	switch (timeCount)
	{
	case 1:
		CanSend(0x1, 1);
		break;
	case 2:
		CanSend(0x2, 2);
		break;
	case 3:
		timeCount = 0;
		break;
	default:
		break;
	}
}


void UsbCan::CanConnect() {
	qDebug("CanConnect\n");
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

	bRet = UcanInitHwConnectControlEx(AppConnectControlCallbackEx, this);

	if (bRet == USBCAN_SUCCESSFUL)
	{
		if(UcanInitHardwareEx(&UcanHandle, USBCAN_ANY_MODULE,
			AppEventCallbackEx, this)) emit CanConnected(false);

		if(UcanInitCanEx2(UcanHandle, USBCAN_CHANNEL_CH0,
			&InitParam)) emit CanConnected(false);
	}
	else {
		emit CanConnected(false);
	}
}

void PUBLIC UsbCan::AppConnectControlCallbackEx(DWORD dwEvent_p, DWORD dwParam_p, void* pArg_p)
{
	UsbCan* AAA = (UsbCan*)pArg_p;
	switch (dwEvent_p)
	{
	case USBCAN_EVENT_CONNECT:
		emit AAA->CanConnected(true);
		AAA->timer10->start(25);
		break;
	case USBCAN_EVENT_DISCONNECT:
		emit AAA->CanDisconnected(true);
		AAA->timer10->stop();
		break;
	}
}


void PUBLIC UsbCan::AppEventCallbackEx(tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void* pArg_p){
	
	UsbCan *pThis = reinterpret_cast<UsbCan*>(pArg_p);

	switch (dwEvent_p)
	{

	case USBCAN_EVENT_RECEIVE: // CAN message received
		pThis->CanReceive();
		break;

	case USBCAN_EVENT_STATUS: // changes error status
	// signal that the CAN status can be read SetEvent(ahWaitHandles_g[STATUS]);
		break;

	}

}

void UsbCan::CanDisconnect() {

}

void UsbCan::CanSend(BYTE Id, int type) {
	
	CanTxMsg.m_dwID = Id;
	
	if (type == 1) {
		memcpy(CanTxMsg.m_bData, Tram1, 8);
	}
	else if (type == 2) {
		memcpy(CanTxMsg.m_bData, Tram2, 8);
	}
	UcanWriteCanMsg(UcanHandle, &CanTxMsg);
}


void UsbCan::SetAlt(double altitude) {
	unsigned int alt = (unsigned int)(altitude + ALTSHIFT);
	memcpy(Tram1, &alt, sizeof(int));
}

void UsbCan::SetCap(double cap)
{
	float cp = (float)cap;
	fixed_point_t tmp = (fixed_point_t) round(cp * (1 << FIWED_POINT_FRACTIONAL_BITS_CAP));
	memcpy(Tram1+2, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetVSpeed(double VSpeed) {
	double tmpVal = VSpeed + VSPEEDSHIFT;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_SPEED));
	memcpy(Tram1+4, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetHSpeed(double HSpeed) {
	fixed_point_t tmp = (fixed_point_t)round(HSpeed * (1 << FIWED_POINT_FRACTIONAL_BITS_SPEED));
	memcpy(Tram1+6, &tmp, sizeof(fixed_point_t));
}


void UsbCan::SetPitchDeg(double VSpeed) {
	double tmpVal = VSpeed + DEGSHIFT;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_DEG));
	memcpy(Tram2, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetPitchRate(double HSpeed) {
	double tmpVal = HSpeed + 64;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_RATE));
	memcpy(Tram2+2, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetRollDeg(double VSpeed) {
	double tmpVal = VSpeed + DEGSHIFT;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_DEG));
	memcpy(Tram2+4, &tmp, sizeof(fixed_point_t));
}

void UsbCan::SetRollRate(double HSpeed) {
	double tmpVal = HSpeed + 64;
	fixed_point_t tmp = (fixed_point_t)round(tmpVal * (1 << FIWED_POINT_FRACTIONAL_BITS_RATE));
	memcpy(Tram2+6, &tmp, sizeof(fixed_point_t));
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
	for (int i = 0; i < 8; i++)
	{
		Tram1[i] = 0;
		Tram2[i] = 0;
	}
}

void UsbCan::CanReceive()
{
	dwRxCount = 100;
	bRet = UcanReadCanMsg(UcanHandle, &CanRxMsg);
	if (CanRxMsg.m_dwID == 0x11) {
		memcpy(&throttleCan, CanRxMsg.m_bData, 4);
		emit CanThrottle(throttleCan);
	}
	if (CanRxMsg.m_dwID == 0x12) {
		memcpy(&yokex, CanRxMsg.m_bData, 4);
		memcpy(&yokey, CanRxMsg.m_bData+4, 4);
		emit CanYoke(yokex, yokey);
	}
}
